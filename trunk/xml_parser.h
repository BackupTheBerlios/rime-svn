#include <iostream>
#include <vector>

using namespace std;


#define ELEMENT_NAMESZ 100
#define ELEMENT_VALUESZ 1024

typedef struct _elementT
{
    char m_szName[ELEMENT_NAMESZ];
    char m_szValue[ELEMENT_VALUESZ];
} elementT;




class CXMLParser
{
    private:
	int m_state;
	
    public:
	vector <elementT> elementsList;
	int load_file(const char * szFilename);
	char *  getElement(const char * szElName);
	
	void setState(int state) { m_state = state;}
	int  getState(){ return m_state;}
	int print_list();
	
};
