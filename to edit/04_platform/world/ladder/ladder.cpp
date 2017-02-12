#include "ladder.h"
#include <cstdlib>
#include <fstream>

Ladder::Ladder()
{
	width = 0;
	screen_w = 0;
}

Ladder::~Ladder()
{
	free();
}

void Ladder::free()
{
	width = 0;
	screen_w = 0;
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	if( !planks.empty() )
	{
		for( auto &it :planks )
		{
			it->free();
		}
		
		planks.clear();
	}
}

void Ladder::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :planks )
			{
				it->x ++;
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
}

void Ladder::load( int type, int width, int screen_w )
{
	free();
	
	for( int i = 0; i < 2; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "ladder-sprites[" +to_string( i ) +"]" );
		sprites[ i ]->load( "data/sprites/play/ladder/" +to_string( type ) +"/" +to_string( i ) +".png" );
	}
	
	this->width = width;
	this->screen_w = screen_w;
}

void Ladder::draw( sf::RenderWindow* &window )
{
	for( auto &it :planks )
	{
		if( it->x > -width && it->x < screen_w +width )
		{
			sprites[ it->nr ]->setPosition( it->x, it->y );
			window->draw( sprites[ it->nr ]->get() );
		}
	}
}

void Ladder::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Ladder::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



int Ladder::to_int( string s )
{
	bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-' )
    {
		i++;
		m = true;
    }
	
    while( i < s.size() )
    {
		tmp = 10*tmp +s[ i ] -48;
		i++;
    }
	
    return m ? -tmp : tmp; 
}



void Ladder::positioning( vector <Block*> planks )
{
	for( unsigned i = 0; i < planks.size(); i++ )
	{
		this->planks.push_back( new Block() );
		this->planks[ this->planks.size() -1 ]->x = planks[ i ]->x;
		this->planks[ this->planks.size() -1 ]->y = planks[ i ]->y;
		this->planks[ this->planks.size() -1 ]->nr = planks[ i ]->nr;
	}
}

void Ladder::shrink()
{
	bool end = false;
	while( !end )
	{
		end = true;
		for( unsigned i = 0; i < planks.size(); i++ )
		{
			for( unsigned j = 0; j < planks.size(); j++ )
			{
				if( j != i )
				{
					int value = planks[ j ]->x -planks[ i ]->x;
					if( value < 0 )	value = -value;
					
					if( value < width )
					{
						// printf( "happend %d\n", planks[ i ]->x );
						
						if( planks[ j ]->nr < planks[ i ]->nr )
						{
							planks.erase( planks.begin() +j );
						}
						else
						{
							planks.erase( planks.begin() +i );
						}
						
						end = false;
					}
				}
			}
		}
	}
}



void Ladder::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :planks )
		{
			it->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :planks )
		{
			it->x -= vel;
		}
	}
}

void Ladder::undoFall( sf::Uint8 add )
{
	for( auto &it :planks )
	{
		it->x += add;
	}
}

void Ladder::setColor( sf::Color color )
{
	
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



int Ladder::getW( sf::Uint8 nr )
{
	return sprites[ nr ]->getWidth();
}

int Ladder::getH( sf::Uint8 nr )
{
	return sprites[ nr ]->getHeight();
}



bool Ladder::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :planks )
		{
			if( it->x > -width && it->x < screen_w +width )
			{
				sprites[ it->nr ]->setPosition( it->x, it->y );
				if( sprites[ it->nr ]->checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}