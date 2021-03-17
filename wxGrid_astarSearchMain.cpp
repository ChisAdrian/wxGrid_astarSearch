/***************************************************************
 * Name:      wxGrid_astarSearchMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2021-03-17
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#include "wxGrid_astarSearchMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(wxGrid_astarSearchFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(wxGrid_astarSearchFrame)
const long wxGrid_astarSearchFrame::ID_BUTTON1 = wxNewId();
const long wxGrid_astarSearchFrame::ID_GRID1 = wxNewId();
const long wxGrid_astarSearchFrame::idMenuQuit = wxNewId();
const long wxGrid_astarSearchFrame::idMenuAbout = wxNewId();
const long wxGrid_astarSearchFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(wxGrid_astarSearchFrame,wxFrame)
    //(*EventTable(wxGrid_astarSearchFrame)
    //*)
END_EVENT_TABLE()

wxGrid_astarSearchFrame::wxGrid_astarSearchFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(wxGrid_astarSearchFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(919,468));
    Button1 = new wxButton(this, ID_BUTTON1, _("Label"), wxPoint(16,8), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Grid1 = new wxGrid(this, ID_GRID1, wxPoint(24,56), wxSize(856,392), 0, _T("ID_GRID1"));
    Grid1->CreateGrid(100,100);
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&wxGrid_astarSearchFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxGrid_astarSearchFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&wxGrid_astarSearchFrame::OnAbout);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&wxGrid_astarSearchFrame::OnResize);
    //*)
}

wxGrid_astarSearchFrame::~wxGrid_astarSearchFrame()
{
    //(*Destroy(wxGrid_astarSearchFrame)
    //*)
}

void wxGrid_astarSearchFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void wxGrid_astarSearchFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


#include "astarsearch.h"

 mPath step_node( std::vector<std::vector<int>>  walk_table, std::vector<Pair> picks , Pair start , Pair &endof)
{

    std::vector<mPath> Found;
    std::vector<std::vector<int>>PTH ;


    for(auto i=0;i<picks.size();i++)
    {
        PTH = aStarSearch (walk_table, start,picks.at(i));
        Found.push_back(PTH);
    }

    size_t init_s = 0;
    int index_of_min ;
    for (int i = Found.size() - 1;i>= 0; --i)
    {
        if(init_s==0)
        {
            init_s = Found.at(i).size();
            index_of_min = i;
        }
        if( Found.at(i).size() < init_s)
        {
            init_s  =  Found.at(i).size();
            index_of_min = i;

        }
    }


    endof = std::make_pair(Found.at(index_of_min).at(0).at(0) ,Found.at(index_of_min).at(0).at(1));
    return Found.at(index_of_min);

}


void remove_found_node(std::vector<Pair> &All_Nodes , Pair endof)
{
    for(auto i = 1; i< All_Nodes.size();i++)
    {
        for(size_t l=0;l<All_Nodes.size();l++)
        {
            if (endof == All_Nodes[l])
                All_Nodes.erase(All_Nodes.begin()+ int(l));
        }
    }
}

  std::vector<mPath> Colect_Route(  std::vector<std::vector<int>> walk_table , std::vector<Pair> All_Nodes,Pair  begin_point )
  {


    auto start =  begin_point ;//

    std::vector<mPath> Colect_Route;
    Pair endof;
    size_t size_loop = All_Nodes.size();

    for(size_t i=0;i<size_loop;i++ )
    {
        Colect_Route.push_back(step_node(walk_table,All_Nodes,start,endof));
        remove_found_node( All_Nodes ,  endof);
        start = endof;
    }

   return Colect_Route;

  }




void wxGrid_astarSearchFrame::OnButton1Click(wxCommandEvent& event)
{
     std::vector<std::vector<int>> walk_table
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1},
        {1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1}

    };


    for(int i=0;i<walk_table.size();i++ )
    {
         for(int c=0;c<walk_table.at(0).size();c++ )
         {
             Grid1->SetCellValue(i,c, wxString::FromDouble( walk_table[i][c])  );
             if(  walk_table[i][c] == 0) Grid1->SetCellBackgroundColour(i,c, wxColor("Black"));
             if(  walk_table[i][c] == 1) Grid1->SetCellValue(i,c, "");
         }
    }

     for(int c=0;c<walk_table.at(0).size();c++ )
        Grid1->SetColLabelValue(c,wxString::FromDouble(c,0));

    for(int i=0;i<walk_table.size();i++ )
        Grid1->SetRowLabelValue(i,wxString::FromDouble(i,0));


    Grid1->AutoSizeColumns();

    std::vector<Pair> All_Nodes;

        All_Nodes.push_back(std::make_pair(23,59));
        All_Nodes.push_back(std::make_pair(2,40));
        All_Nodes.push_back(std::make_pair(23,79));
        All_Nodes.push_back(std::make_pair(12,19));
        All_Nodes.push_back(std::make_pair(8,6));
        All_Nodes.push_back(std::make_pair(1,30));
        All_Nodes.push_back(std::make_pair(18,40));
        All_Nodes.push_back(std::make_pair(17,53));
        All_Nodes.push_back(std::make_pair(23,13));
        All_Nodes.push_back(std::make_pair(24,79));

    auto minR = Colect_Route(walk_table,All_Nodes,std::make_pair(0, 0));

    size_t loop_minR = minR.size();
      for(auto r = 0;r<loop_minR ;r++)
      {
            auto minPTH =  minR.at(r);
            for (int i = minPTH.size() - 1; i >= 0; --i)
            {
                if(Grid1->GetCellValue(minPTH.at(i).at(0), minPTH.at(i).at(1) ) =="")
                {
                    Grid1->SetCellValue(minPTH.at(i).at(0), minPTH.at(i).at(1),"*");
                    Grid1->SetCellBackgroundColour(minPTH.at(i).at(0), minPTH.at(i).at(1),wxColor("Green"));
                }
                if (i ==  minPTH.size() - 1 )
                {
                    Grid1->SetCellBackgroundColour(minPTH.at(i).at(0), minPTH.at(i).at(1),wxColor("Red"));
                    Grid1->SetCellValue(minPTH.at(i).at(0), minPTH.at(i).at(1),
                    Grid1->GetCellValue(minPTH.at(i).at(0), minPTH.at(i).at(1) )+ "," +
                             wxString::FromDouble(r) );

                }
            }
      }

        auto LastPath =  minR[loop_minR-1];
        Grid1->SetCellBackgroundColour(LastPath.at(0).at(0),  LastPath.at(0).at(1), wxColor("Red"));
         Grid1->SetCellValue(LastPath.at(0).at(0),  LastPath.at(0).at(1),
                             Grid1->GetCellValue(LastPath.at(0).at(0),  LastPath.at(0).at(1)) + "," +
                             wxString::FromDouble(loop_minR));

    Grid1->AutoSizeColumns();
    Grid1->Refresh();

}

void wxGrid_astarSearchFrame::OnResize(wxSizeEvent& event)
{
    int width,height;
    this->GetClientSize(&width,&height);
    Grid1->SetSize(16,72,width-30,height - 72 - 30);
}
