


#ifndef __SHARP_XMLWRITER_HPP_
#define __SHARP_XMLWRITER_HPP_

#include <string>

#include <boost/noncopyable.hpp>

#include <libxml/xmlwriter.h>


namespace sharp {

	class XmlWriter
		: public boost::noncopyable
	{
	public:
		XmlWriter();
		XmlWriter(const std::string & filename);		
		~XmlWriter();
		int write_start_document()
			{
				return xmlTextWriterStartDocument(m_writer, NULL, NULL, NULL);
			}
		int write_end_document()
			{
				return xmlTextWriterEndDocument(m_writer);
			}
		int write_start_element(const std::string & prefix, const std::string & name, const std::string & nsuri)
			{
				return xmlTextWriterStartElementNS(m_writer, (const xmlChar*)prefix.c_str(), 
																			 (const xmlChar*)name.c_str(), (const xmlChar*)nsuri.c_str());
			}
		int write_end_element()
			{
				return xmlTextWriterEndElement(m_writer);
			}
		int write_attribute_string(const std::string & prefix,const std::string & local_name,
															 const std::string & ns ,const std::string & value)
			{
				return xmlTextWriterWriteAttributeNS(m_writer, (const xmlChar*)prefix.c_str(), 
																				(const xmlChar*)local_name.c_str(),
																				(const xmlChar*)ns.c_str(), (const xmlChar*)value.c_str());
			}
		int write_raw(const std::string & raw)
			{
				return xmlTextWriterWriteRaw(m_writer, (const xmlChar*)raw.c_str());
			}
		int write_string(const std::string & );

		int close();
		std::string to_string();

	private:
		xmlTextWriterPtr m_writer;
		xmlBufferPtr     m_buf;
	};

}

#endif

