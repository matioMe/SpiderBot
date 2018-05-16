#include "xml.h"
#include <boost/lexical_cast.hpp>

using namespace std;

XML::XML(string fileName)
{
    m_fileName = "/home/anon-d/Bureau/"+fileName+".xml";
    m_fileString = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<?mso-application progid=\"Excel.Sheet\"?>\n<Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:c=\"urn:schemas-microsoft-com:office:component:spreadsheet\" xmlns:html=\"http://www.w3.org/TR/REC-html40\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:x2=\"http://schemas.microsoft.com/office/excel/2003/xml\" xmlns:x=\"urn:schemas-microsoft-com:office:excel\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"><OfficeDocumentSettings xmlns=\"urn:schemas-microsoft-com:office:office\">\n<Colors>\n<Color>\n<Index>3</Index>\n<RGB>#c0c0c0</RGB>\n</Color>\n<Color>\n<Index>4</Index>\n<RGB>#ff0000</RGB>\n</Color>\n</Colors>\n</OfficeDocumentSettings>\n<ExcelWorkbook xmlns=\"urn:schemas-microsoft-com:office:excel\">\n<WindowHeight>9000</WindowHeight>\n<WindowWidth>13860</WindowWidth>\n<WindowTopX>240</WindowTopX>\n<WindowTopY>75</WindowTopY>\n<ProtectStructure>False</ProtectStructure>\n<ProtectWindows>False</ProtectWindows>\n</ExcelWorkbook>\n<Styles>\n<Style ss:ID=\"Default\" ss:Name=\"Default\"/>\n<Style ss:ID=\"Result\" ss:Name=\"Result\">\n<Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Underline=\"Single\"/>\n</Style>\n<Style ss:ID=\"Result2\" ss:Name=\"Result2\">\n<Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Underline=\"Single\"/>\n<NumberFormat ss:Format=\"Euro Currency\"/>\n</Style>\n<Style ss:ID=\"Heading\" ss:Name=\"Heading\">\n<Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Size=\"16\"/>\n</Style>\n<Style ss:ID=\"Heading1\" ss:Name=\"Heading1\">\n<Font ss:Bold=\"1\" ss:Italic=\"1\" ss:Size=\"16\"/>\n</Style>\n<Style ss:ID=\"co1\"/>\n<Style ss:ID=\"ta1\"/>\n</Styles>\n<ss:Worksheet ss:Name=\"Feuille1\">\n<Table ss:StyleID=\"ta1\">\n<Column ss:Span=\"1\" ss:Width=\"64,0063\"/>\n";

}

XML::~XML()
{

}

int XML::generateFile(float values[], int nbColumn, int nbRaws) //sizeof?
{
    if(m_file = new ofstream(m_fileName, (ios::out | ios::trunc)))
    {
        for(int i=0; i<nbRaws; i++)
        {
            m_fileString+="<Row ss:Height=\"12,8126\">\n";
            for(int j=0; j<nbColumn; j++)
            {
                m_fileString+="<Cell><Data ss:Type=\"Number\">";
                m_fileString+=boost::lexical_cast<std::string>(values[i*nbColumn+j]); //transforme un float en string
                m_fileString+="</Data></Cell>\n";
            }
            m_fileString+="</Row>\n";
        }
        m_fileString+="</Table><x:WorksheetOptions/></ss:Worksheet></Workbook>";
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


