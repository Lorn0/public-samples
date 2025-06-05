#include "cMain.h"

wxBEGIN_EVENT_TABLE( cMain, wxFrame )
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame( nullptr, wxID_ANY, "Minesweeper by Lorn0", wxPoint( 50, 50 ), wxSize( 796, 600 ), wxDEFAULT_FRAME_STYLE & ~( wxRESIZE_BORDER | wxMAXIMIZE_BOX ) )
{
    //Maximize( true );
    btn = new wxButton * [ nFieldWidth * nFieldHeight ];
    wxGridSizer* grid = new wxGridSizer( nFieldHeight, nFieldWidth, 0, 0 );

    nField = new int[ nFieldWidth * nFieldHeight ];

    wxFont font( 24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false );

    for( int i = 0; i < nFieldWidth; i++ ) 
    {
        for( int j = 0; j < nFieldHeight; j++ ) 
        {
            btn[ j * nFieldWidth + i ] = new wxButton( this, 10000 + ( j * nFieldWidth + i ) );
            btn[ j * nFieldWidth + i ]->SetFont( font );
            grid->Add( btn[ j * nFieldWidth + i ], 1, wxEXPAND | wxALL );

            btn[ j * nFieldWidth + i ]->Bind( wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this );
            nField[ j * nFieldWidth + i ] = 0;
        }
    }
    
    this->SetSizer( grid );
    grid->Layout();

}

cMain::~cMain()
{
   //preventing memory leaks 
    delete[]btn;
    delete[]nField;
}

void cMain::OnButtonClicked( wxCommandEvent& evt )
{
   //Get coordinates of button in field array
    int x = ( evt.GetId() - 10000 ) % nFieldWidth;
    int y = ( evt.GetId() - 10000 ) / nFieldWidth;

   //after first click populate minefield ( so u dont die over and over on first click )
    if( bFirstClick ) 
    {
       //how many mines get placed on the Field
        int mines = 30;

        while( mines ) 
        {
           //get random x and y coordinates for the mines
            int rx = rand() % nFieldWidth;
            int ry = rand() % nFieldHeight;

           //check if this coordinate is valid (has a button and if it has does this button already contain a mine)
            if( nField[ ry * nFieldWidth + rx ] == 0 && ry != x && ry != y ) 
            {
                nField[ ry * nFieldWidth + rx ] = -1; // -1 indicates presence of a mine
                mines--;
            }

        }

        bFirstClick = false;

    }

   //Disable Button preventing it from being pressed again
    btn[ y * nFieldWidth + x ]->Enable( false );

   //Check if player hit a mine if yes -> game over (-1 indicades mine)
    if( nField[ y * nFieldWidth + x ] == -1 ) 
    {
        wxMessageBox( "BOOOM !! - Game Over try again!" );

       //reset gamestate
        bFirstClick = true;
        for( int i = 0; i < nFieldWidth; i++ )
            for( int j = 0; j < nFieldHeight; j++ ) 
            {
                nField[ j * nFieldWidth + i ] = 0;
                btn[ j * nFieldWidth + i ]->SetLabel( "" );
                btn[ j * nFieldWidth + i ]->Enable( true );

            }

    }
    else 
    {
       /* //if not -> win_count (we have 10x10 = 100 buttons and 30 mines so if we get 70 valid clicks without exploding we win // taek another look doesnt work
        int win_count = 0;
        win_count++;

        if( win_count >= 70 ) 
        {
            //if wincount >= 70 -> game won
            wxMessageBox( "Congrats u won! - tray again anyways!" );

            //reset gamestate
            bFirstClick = true;
            for( int i = 0; i < nFieldWidth; i++ )
                for( int j = 0; j < nFieldHeight; j++ ) {
                    nField[ j * nFieldWidth + i ] = 0;
                    btn[ j * nFieldWidth + i ]->SetLabel( "" );
                    btn[ j * nFieldWidth + i ]->Enable( true );

                }
        }
        */

       //count mines that are close to last location
        int mine_count = 0;
        for (int i = -1; i < 2; i++ )
            for( int j = -1; j < 2; j++ ) 
            {
                if( x + i >= 0 && x + i < nFieldWidth && y + j >= 0 && y + j < nFieldHeight ) 
                {
                    if( nField[ ( y + j ) * nFieldWidth + ( x + i ) ] == -1 )
                        mine_count++;

                }
            }

       //update button labels to show minecount if > 0 
        if( mine_count > 0 ) 
        {
            btn[ y * nFieldWidth + x ]->SetLabel( std::to_string( mine_count ) );

            if( mine_count > -1 )                 
            {
                btn[ y * nFieldWidth + x ]->Enable( false );
            }
        }

    }


   //skipping all parents after the initial window couldnt handle the event
    evt.Skip();
}