/*
*
*/
#include <qfont.h>
#include <qcolor.h>

#include "PPStyleSheet.h"


PPStyleSheet::PPStyleSheet() : Q3StyleSheet() 
{
	Q3StyleSheetItem* i;
	
	// qt
	i = item( "qt" );
	i->setFontFamily( "Arial" );
	i->setMargin( Q3StyleSheetItem::MarginBottom, 40 );

	// h1
	i = item( "h1" );
	i->setFontUnderline( false );
	i->setLogicalFontSize( 7 );

	// h2
	i = item( "h2" );
	i->setFontUnderline( false );
	i->setLogicalFontSize( 6 );

    	// h3
	i = item( "h3" );
	i->setFontUnderline( false );
	i->setLogicalFontSize( 5 );

	// b
	i = item( "b" );
	i->setMargin( Q3StyleSheetItem::MarginLeft, 20 );
	i->setLogicalFontSize( 3 );

	// p
	i = item( "p" );
	i->setMargin( Q3StyleSheetItem::MarginLeft, 20 );
	i->setLogicalFontSize( 3 );


}
