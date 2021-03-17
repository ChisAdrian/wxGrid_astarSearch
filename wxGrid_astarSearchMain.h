/***************************************************************
 * Name:      wxGrid_astarSearchMain.h
 * Purpose:   Defines Application Frame
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2021-03-17
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#ifndef WXGRID_ASTARSEARCHMAIN_H
#define WXGRID_ASTARSEARCHMAIN_H

//(*Headers(wxGrid_astarSearchFrame)
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/grid.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class wxGrid_astarSearchFrame: public wxFrame
{
    public:

        wxGrid_astarSearchFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~wxGrid_astarSearchFrame();

    private:

        //(*Handlers(wxGrid_astarSearchFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnResize(wxSizeEvent& event);
        //*)

        //(*Identifiers(wxGrid_astarSearchFrame)
        static const long ID_BUTTON1;
        static const long ID_GRID1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(wxGrid_astarSearchFrame)
        wxButton* Button1;
        wxGrid* Grid1;
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WXGRID_ASTARSEARCHMAIN_H
