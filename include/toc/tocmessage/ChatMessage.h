/**
 * @file
 *
 * @author  Karol Herbst
 * @since   0.1
 *
 * @section LICENSE
 *
 * @section DESCRIPTION
 */

#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP 1

#include <boost/extension/impl/decl.hpp>
#include <TocEnv/TocEnv.h>
#include <toc/tocstring/TocString.h>

#ifndef DLL_TOC_MESSAGE
#ifdef MAKE_TOC_MESSAGE
#define DLL_TOC_MESSAGE BOOST_EXTENSION_EXPORT_DECL
#else
#define DLL_TOC_MESSAGE BOOST_EXTENSION_IMPORT_DECL
#endif
#endif

namespace TOC
{
    namespace message
    {
        /**
         * readonly class for reading incoming data for the TOC protocol
         *
         * @class   ChatMessage
         * @author  Karol Herbst
         * @since   0.1
         */
        class DLL_TOC_MESSAGE ChatMessage
        {
        public:
            /**
             * copy constructor
             *
             * @author  Karol Herbst
             * @since   0.1
             *
             * @param   cm  ChatMessage Object to copy
             */
            ChatMessage(const ChatMessage & cm);
            
            /**
             * receiving constructor
             *
             * use this class to convert raw data to readable data
             *
             * @author  Karol Herbst
             * @since   0.1
             *
             * @param   data    raw data as binary array
             */
            ChatMessage(const char * data);
            
            /**
             * sending constructor
             *
             * @see     ChatMessage::ChatMessage(const char *, uint16_t)
             *
             * @author  Karol Herbst
             * @since   0.1
             *
             * @param   message the message to send as string object
             */
            ChatMessage(const std::string & message);
            
            /**
             * C-style sending constructor
             *
             * @see     ChatMessage::ChatMessage(const String &)
             *
             * @author  Karol Herbst
             * @since   0.1
             *
             * @param   body        the body part to send (normally a C-String based like
             *                      string or other raw data
             * @param   bodyLength  the length of body
             */
            ChatMessage(const char * body,
                        uint16_t bodyLength);
            
            /**
             * Full constructor
             *
             * @param    body        the body part
             * @param    bodyLength  the length of body
             * @param    time        UNIX timestamp
             *
             * @author    Karol Herbst
             * @since    0.1.1
             */
            ChatMessage(const char * body,
                        uint16_t bodyLength,
                        time_t time);
            /**
             * destructor
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            ~ChatMessage();
            
            /**
             * struct providing array indexes for specific data
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            private: struct HEADER_DATA
            {
                /**
                 * specify the position of the message flags
                 *
                 * @author  Karol Herbst
                 * @since   0.1
                 */
                static const uint16_t FLAG_POS;
                /**
                 * specify the position of body length int value
                 *
                 * @author  Karol Herbst
                 * @since   0.1
                 */
                static const uint16_t BODY_LENGTH_POS;
            };
            
            public:
            /**
             * enumeration for special flags
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            SCOPED_ENUM(MESSAGE_FLAGS, uint16_t)
            {
                /**
                 * specify whether the raw data is binary or not
                 *
                 * @author  Karol Herbst
                 * @since   0.1
                 */
                IS_BINARY     = 0x0001,
                
                /**
                 * specify whether the raw data is compressed or not
                 *
                 * @author  Karol Herbst
                 * @since   0.1
                 */
                IS_COMPRESSED = 0x0002
            };
            
            /**
             * return the whole raw data saved in this object
             *
             * the returning C-String will be deallocated when the ChatMessage
             * object is destroyed. Use it to send the raw data through network
             * or something else.
             * AGAIN: DO NOT DELETE THIS ARRAY!
             *
             * @author  Karol Herbst
             * @since   0.1
             * @return  the internal raw data
             */
            const char *    data();
            
            /**
             * the length of the header part
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            static const uint16_t headerLength;
            
            /**
             * the length of the timestamp part
             *
             * @author  Karol Herbst
             * @since   0.1
             */
            static const uint32_t timestampLength;
            
            /**
             * reads information about body length
             *
             * @author  Karol Herbst
             * @since   0.1
             * @return  the length of the body
             * @param   headerOrRawData this can be a header part or the whole
             *                          raw data.
             */
            static uint16_t bodyLengthFromHeader(const char* headerOrRawData);
            
            /**
             * @author  Karol Herbst
             * @since   0.1
             * @return  length of the whole raw data
             */
            uint16_t        length() const;
            
            /**
             * @author  Karol Herbst
             * @since   0.1
             * @return  the length of the body part
             */
            uint16_t        bodyLength() const;
            
            /**
             * @author  Karol Herbst
             * @since   0.1
             * @return  a string class copy of the body
             * @see     ChatMessage::bodyBinary()
             */
            std::string     body() const;
            
            /**
             * through these method you can access the raw body data
             *
             * copy the returning C-string if you ned it. This method do NOT
             * returns a copy.
             *
             * @author  Karol Herbst
             * @since   0.1
             * @return  thw C-string of the body
             */
            const char*     bodyBinary() const;
            
            /**
             * @author  Karol Herbst
             * @since   0.1
             * @return  the timestamp stored in the raw data
             */
            int64_t         timestamp() const;
            
        private:
            char*           _body_() const;
            
            void            setData(const char*);
            
            void            setData(const std::string& body);
            void            setData(const char* body,
                                    uint16_t bodyLength);
            void            setData(const char* body,
                                    uint16_t bodyLength,
                                    time_t timestamp);
            char*           __databuffer__;
        };
    }
}

#endif // CHAT_MESSAGE_HPP