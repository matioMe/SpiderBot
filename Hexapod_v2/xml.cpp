#include "xml.h"
#include <boost/lexical_cast.hpp>

using namespace std;

XML::XML(string fileName)
{
    m_fileName = "/home/anon-d/Bureau/"+fileName+".xml";
    m_fileString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><?mso-application progid=\"Excel.Sheet\"?><Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:c=\"urn:schemas-microsoft-com:office:component:spreadsheet\" xmlns:html=\"http://www.w3.org/TR/REC-html40\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:x2=\"http://schemas.microsoft.com/office/excel/2003/xml\" xmlns:x=\"urn:schemas-microsoft-com:office:excel\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><OfficeDocumentSettings xmlns=\"urn:schemas-microsoft-com:office:office\"><Colors><Color><Index>3</Index><RGB>#c0c0c0</RGB></Color><Color><Index>4</Index><RGB>#ff0000</RGB></Color></Colors></OfficeDocumentSettings><ExcelWorkbook xmlns=\"urn:schemas-microsoft-com:office:excel\"><WindowHeight>9000</WindowHeight><WindowWidth>13860</WindowWidth><WindowTopX>240</WindowTopX><WindowTopY>75</WindowTopY><ProtectStructure>False</ProtectStructure><ProtectWindows>False</ProtectWindows></ExcelWorkbook><Styles><Style ss:ID=\"Default\" ss:Name=\"Default\"/><Style ss:ID=\"Result\" ss:Name=\"Result\"><Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Underline=\"Single\"/></Style><Style ss:ID=\"Result2\" ss:Name=\"Result2\"><Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Underline=\"Single\"/><NumberFormat ss:Format=\"Euro Currency\"/></Style><Style ss:ID=\"Heading\" ss:Name=\"Heading\"><Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Size=\"16\"/></Style><Style ss:ID=\"Heading1\" ss:Name=\"Heading1\"><Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Size=\"16\"/></Style><Style ss:ID=\"co1\"/><Style ss:ID=\"ta1\"/></Styles><ss:Worksheet ss:Name=\"Feuille1\"><Table ss:StyleID=\"ta1\"><Column ss:Span=\"1\" ss:Width=\"64,0063\"/>";

}

XML::~XML()
{

}

int XML::generateFile(float values[], int nbColumn) //sizeof?
{
    if(m_file = new ofstream(m_fileName, (ios::out | ios::trunc)))
    {
        //int tableSize=sizeof(values);
        //int nbRaws=tableSize/sizeof(float);
        int nbRaws=100;
        m_fileString+="<ss:Worksheet ss:Name=\"Feuille1\"><Table ss:StyleID=\"ta1\"><Column ss:Span=\"1\" ss:Width=\"64,0063\"/>";
        for(int i=1; i<nbColumn+1; i++)
        {
            m_fileString+="<Row ss:Height=\"12,8126\">";
            for(int j=1; j<nbRaws+1; j++)
            {
                m_fileString+="<Cell><Data ss:Type=\"Number\">";
                m_fileString+=boost::lexical_cast<std::string>(values[i*j]);
                m_fileString+="</Data></Cell>";
            }
            m_fileString+="</Row>";
        }
        m_fileString+="</Table><x:WorksheetOptions/></ss:Worksheet>";
        *m_file<<m_fileString<<endl;
        m_file->close();
        return 0;
    }
    else
    {
        cout<<"impossible to open the file."<<endl;
        return 1;
    }
}


