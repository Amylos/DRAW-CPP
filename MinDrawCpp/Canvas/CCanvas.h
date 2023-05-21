/*
 * CCanvas.h
 *
 *  Created on: 7 oct. 2022
 *      Author: Garnier
 */

#ifndef CCANVAS_H_
#define CCANVAS_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<CContainer.h>
#include<CArea.h>
#include<CShape.h>


#include<CShape.h>
#include<CSrectangle.h>
#include<CStriangle.h>
#include<CScircle.h>
#include<CSpolygon.h>

class CCanvas : public CArea{
private:
	CContainer	m_Shapes{(t_ptfV) CCanvas::ShapeDeleteMethod};
	CCanvas();
public:
	CCanvas(int iLocX,int iLocY,int iWidth,int iHeight,SDL_Color color);
	~CCanvas();

	SDL_Rect GetFrame();

	CShape*AddShape(CShape*pShape);
	void Draw(SDL_Renderer*pRenderer) const;
	void Flush();
	void Serialize();
	void Unserialize();
	void DeleteShape(SDL_Point pAt);
	CShape*ShapeIsAt(SDL_Point pAt);

	static CShape*ShapeDeleteMethod(CShape*pShape);
	static CShape*ShapeDrawMethod(CShape*pShape, SDL_Renderer*pRenderer);
	static CShape*SerializeMethod(CShape*pShape,FILE*fd);
	static CShape*ShapeIsAtMethod(CShape*pShape,SDL_Point*pAt);

	static CShape*DragMethod(CShape*pShape,SDL_Point pAt);


};

#endif /* CCANVAS_H_ */
