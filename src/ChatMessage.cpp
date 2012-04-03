/*
 *  chatMessage.cpp
 *  Projekt
 *
 *  Created by Karol Herbst on 17.02.11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <toc/tocmessage/ChatMessage.h>
#include <cstring>

namespace TOC
{
    namespace message
    {
        const uint16_t ChatMessage::headerLength = 6;
        const uint32_t ChatMessage::timestampLength = 8;
        
        ChatMessage::ChatMessage(const ChatMessage& cm)
        {
            setData(cm.bodyBinary(),
                    cm.bodyLength());
        }
        
        ChatMessage::ChatMessage(const char* data)
        {
            setData(data);
        }
        
        ChatMessage::ChatMessage(const std::string& message)
        {
            setData(message);
        }
        
        ChatMessage::ChatMessage(const char* body,
                                 uint16_t bodyLength)
        {
            setData(body, bodyLength);
        }
        
        ChatMessage::~ChatMessage()
        {
            delete[] __databuffer__;
        }
        
        /*
         * we don't need this anymore, because the data doesn't change after object creation
         */
        const char* ChatMessage::data()
        {
            return __databuffer__;
        }
        
        void ChatMessage::setData(const char* data)
        {
            setData(&data[headerLength + timestampLength],
                    bodyLengthFromHeader(data));
        }
        
        void ChatMessage::setData(const char* body,
                                  uint16_t bodyLength)
        {
            setData(body,
                    bodyLength,
                    0);
        }
        
        void ChatMessage::setData(const std::string& body)
        {
            setData(body.c_str(),
                    body.size());
        }
        
        void ChatMessage::setData(const char* body,
                                  uint16_t bodyLength,
                                  time_t timestamp)
        {
            __databuffer__ = new char[headerLength + timestampLength + bodyLength + 1];
            
            // bodyLength
            __databuffer__[HEADER_DATA::BODY_LENGTH_POS] = bodyLength >> 8;
            __databuffer__[HEADER_DATA::BODY_LENGTH_POS + 1] = bodyLength & 0x00ff;
            
            // copy timestamp into datastream
            memcpy(&__databuffer__[headerLength],
                   &timestamp,
                   timestampLength);

            // compress here
            memcpy(_body_(),
                   body,
                   bodyLength);
            __databuffer__[headerLength + timestampLength + bodyLength] = '\0';
        }
        
        uint16_t ChatMessage::length() const
        {
            return headerLength + timestampLength + bodyLength();
        }
        
        uint16_t ChatMessage::bodyLength() const
        {
            return bodyLengthFromHeader(__databuffer__);
        }
        
        const char* ChatMessage::bodyBinary() const
        {
            return _body_();
        }
        
        std::string ChatMessage::body() const
        {
            return std::string(_body_(), bodyLength());
        }
        
        int64_t ChatMessage::timestamp() const
        {
            return 0;
        }
        
        uint16_t ChatMessage::bodyLengthFromHeader(const char* _header)
        {
            return _header[HEADER_DATA::BODY_LENGTH_POS] << 8
                | (_header[HEADER_DATA::BODY_LENGTH_POS + 1] & 0xff);
        }
        
        char* ChatMessage::_body_() const
        {
            return &__databuffer__[headerLength + timestampLength];
        }
        
        const uint16_t ChatMessage::HEADER_DATA::FLAG_POS = 0;
        const uint16_t ChatMessage::HEADER_DATA::BODY_LENGTH_POS = 2;
    }
}
