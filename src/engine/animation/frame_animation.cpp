#include "frame_animation.h"
#include "graphics/texture_manager.h"

FrameAnimation::FrameAnimation(std::string file, Transform *objTf) {
    if (Parse(ANIMATION_FOLDER + file)) {
        m_CurrentSeq = m_SeqMap.begin()->second;
        m_ObjectTransform->Width = m_CurrentSeq->Width * m_ObjectTransform->ScaleX;
        m_ObjectTransform->Height = m_CurrentSeq->Height * m_ObjectTransform->ScaleY;
    }
}

FrameAnimation::~FrameAnimation() {
    m_CurrentSeq->TextureIDs.clear();
    m_CurrentSeq->TextureIDs.shrink_to_fit();
    m_SeqMap.clear();
}

void FrameAnimation::Draw() {
    TextureManager::GetInstance()->Draw(m_ObjectTransform);
}

void FrameAnimation::Update() {
    if (m_CurrentSeq->FrameCount > 1) {
        m_CurrentFrame = (SDL_GetTicks() / m_CurrentSeq->Speed) % m_CurrentSeq->FrameCount;
    } else {
        m_CurrentFrame = 0;
    }
    m_ObjectTransform->TextureID = m_CurrentSeq->TextureIDs[m_CurrentFrame];
}

bool FrameAnimation::Parse(std::string source) {
    TiXmlDocument xml;
    xml.LoadFile(source.c_str());
    if (xml.Error()) {
        std::cout << "Failed to load animation file: " << source << std::endl;
        return false;
    }

    TiXmlElement *root = xml.RootElement();
    for (TiXmlElement *e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (e->Value() == std::string("sequence")) {
            Sequence *seq = new Sequence();
            std::string seqID = e->Attribute("id");
            e->Attribute("speed", &seq->Speed);
            e->Attribute("width", &seq->Width);
            e->Attribute("height", &seq->Height);
            e->Attribute("frameCount", &seq->FrameCount);
            for (TiXmlElement *frame = e->FirstChildElement(); frame != nullptr; frame = frame->NextSiblingElement()) {
                // std::cout << "frame: " << frame->Attribute("textureID") << std::endl;
                seq->TextureIDs.push_back(frame->Attribute("textureID"));
            }
            m_SeqMap[seqID] = seq;
        }
    }

    if (m_SeqMap.size() > 0) {
        std::cout << source << " animation parsed!" << std::endl;
        return true;
    }

    std::cout << source << " empty animation file!" << std::endl;
    return false;
}

bool FrameAnimation::SetCurrentSeq(std::string seqID) {
    if (m_SeqMap.count(seqID) > 0) {
        m_CurrentSeq = m_SeqMap[seqID];
        m_ObjectTransform->Width = m_CurrentSeq->Width * m_ObjectTransform->ScaleX;
        m_ObjectTransform->Height = m_CurrentSeq->Height * m_ObjectTransform->ScaleY;
        return true;
    }

    std::cout << "Sequence id not found: " << seqID << std::endl;
    return false;
}
