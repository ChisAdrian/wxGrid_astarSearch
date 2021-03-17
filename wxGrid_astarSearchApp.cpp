/***************************************************************
 * Name:      wxGrid_astarSearchApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Adrian Chis (chis.adrian@gmail.com)
 * Created:   2021-03-17
 * Copyright: Adrian Chis ()
 * License:
 **************************************************************/

#include "wxGrid_astarSearchApp.h"

//(*AppHeaders
#include "wxGrid_astarSearchMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxGrid_astarSearchApp);

bool wxGrid_astarSearchApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	wxGrid_astarSearchFrame* Frame = new wxGrid_astarSearchFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
