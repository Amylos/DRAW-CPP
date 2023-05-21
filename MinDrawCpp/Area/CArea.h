/*
 * CArea.h
 *
 *  Created on: 11 oct. 2022
 *      Author: Garnier
 */

#ifndef CAREA_H_
#define CAREA_H_

#include<SDL2/SDL.h>

enum e_toolType{			/* Tool type enumerate definition 	 	 */
	TOOL_UNDEFINED  = 0,	/* undefined tool: no tool			 	 */
	TOOL_CIRCLE     = 1,	/* for drawing circles				 	 */
	TOOL_TRIANGLE   = 4,	/* for drawing triangles			 	 */
	TOOL_RECTANGLE  = 5,	/* for drawing squares or rectangles 	 */
	TOOL_POLYGON    = 7,	/* for drawing free polygons		 	 */
	TOOL_COLORCHART,		/* for placing a color-chart in tool-box,
								in purpose to peek a color			 */
};

class CArea {
protected:
	SDL_Rect 	m_rFrame;
	SDL_Color	m_color;
protected:
	CArea();
public:

	virtual ~CArea();
	CArea(int iLocX,int iLocY,int iWidth, int iHeight, SDL_Color color);

	virtual void Draw(SDL_Renderer*pRenderer)const=0;
};

#endif /* CAREA_H_ */
