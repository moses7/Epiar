/*
 * Filename      : font.cpp
 * Author(s)     : Chris Thielen (chris@luethy.net)
 * Date Created  : Unknown (2006?)
 * Last Modified : Saturday, January 5, 2008
 * Purpose       : 
 * Notes         :
 */

#include "Graphics/font.h"
#include "Graphics/afont/afont_gl.h"
#include "includes.h"
#include "Utilities/log.h"

Font::Font() {
	font = NULL;
	filename = NULL;

	r = 1.;
	g = 1.;
	b = 1.;
}

Font::Font( const char *filename ) {
	font = NULL;
	this->filename = NULL;

	r = 1.;
	g = 1.;
	b = 1.;

	SetFont( filename );
}

Font::~Font() {
	afont_gl_free( font );

	Log::Message( "Font '%s' freed.", filename );

	free( filename );
}

bool Font::SetFont( const char *filename ) {
	font = afont_gl_load( filename );

	if( font == NULL ) {
		Log::Error( "Failed to load font '%s'.\n", filename );
		return( false );
	}

	this->filename = strdup( filename );

	afont_size_text( font->orig, "A", &(this->width), &(this->height), &(this->base));

	Log::Message( "Font '%s' loaded.\n", filename );

	return( true );
}

void Font::Render( int x, int y, const char *text ) {
	glEnable( GL_TEXTURE_2D );
	glEnable(GL_BLEND);

	glColor4f( r, g, b, 1. );
	glRasterPos2i( x, y + height); // + height so that the top corner is at (x,y) like everything else.

	afont_gl_render_text( font, text );
}

// Renders text centered squarely on (x,y), taking the bounding box into account
void Font::RenderCentered( int x, int y, const char *text ) {
	int w, h, base;

	// determine size of text
	afont_size_text( font->orig, text, &w, &h, &base );

	Render( x - (w / 2), y - (h / 2) , text ); // -1 because it just kinda looks better
}

void Font::SetColor( float r, float g, float b ) {
	this->r = r;
	this->g = g;
	this->b = b;
}
