#include <iostream>
#include <stdio.h>
#include <string.h>
#include "expat.h"
#include "xml_parser.h"

using namespace std;

#define WAS_ELEMENT 1
#define WAS_NO_ELEMENT 2

typedef struct _parserData
{
  int depthPtr;
  int state;
} parserData;

static void XMLCALL
startElement(void *userData, const char *name, const char **)
{
  elementT element;
  CXMLParser *data = (CXMLParser *)userData;
    
  data->setState(WAS_NO_ELEMENT);
  if (strcmp (name , "Config") != 0)
    {
      strcpy(element.m_szName , name);
      data->setState ( WAS_ELEMENT );
      data->elementsList.push_back(element);
    }
}

static void XMLCALL
endElement(void *userData, const char *)
{
  CXMLParser * data  = (CXMLParser *)userData;
  data->setState(WAS_NO_ELEMENT);
}


static void XMLCALL
element (void * userData , const char * name , int len)
{
  CXMLParser *data = (CXMLParser *)userData;
  char temp[ELEMENT_VALUESZ];
  int k;
  if ( data->getState() == WAS_ELEMENT)
    {
      memcpy(temp , name , len);
      temp[len] = '\0';
      k = data->elementsList.size();
      strcpy(data->elementsList[k-1].m_szValue , temp);
    }
  data->setState( WAS_NO_ELEMENT);
}


int CXMLParser::load_file(const char * szFilename )
{
  char buf[BUFSIZ];
  XML_Parser parser = XML_ParserCreate(NULL);
  int done;
  
  parserData data;
  data.state = WAS_NO_ELEMENT;
  
  FILE * file = fopen(szFilename , "r");

  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser , element);
  
  do 
    {
      size_t len = fread(buf, 1, sizeof(buf), file);
      done = len < sizeof(buf);
      if (XML_Parse(parser, buf, len, done) == XML_STATUS_ERROR) 
        {
          fprintf(stderr,"%s at line %d\n",
                  XML_ErrorString(XML_GetErrorCode(parser)),
                  XML_GetCurrentLineNumber(parser));
          return 1;
        }
    } while (!done);
  
  fclose (file);
  XML_ParserFree(parser);
 
  return 0;
}

int CXMLParser::print_list()
{
  for (unsigned int i = 0; i < elementsList.size() ; i ++)
	cout << elementsList[i].m_szName << " = " << elementsList[i].m_szValue << endl;
  return 0;
}

char * CXMLParser::getElement(const char * szName)
{
  for (unsigned int i = 0 ; i < elementsList.size() ; i ++)
	if (strcasecmp (elementsList[i].m_szName , szName) == 0)
      return elementsList[i].m_szValue;
  return NULL;
}


// int main()
// {
//     CXMLParser parser;
//     parser.load_file("config.xml");
//     char  * value;
//     value = parser.getElement("Color");
//     if (value != NULL)
//         cout << value<< endl;
//     value = parser.getElement("orice_camp");
//     if (value != NULL)
//         cout << value<< endl;
//     value = parser.getElement("MaPisPeColor");
//     if (value != NULL)
//         cout << value<< endl;
//     value = parser.getElement("BGColor");
//     if (value != NULL)
//         cout << value<< endl;

//     return 0;
// }
