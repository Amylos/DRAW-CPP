/*
 * CShape.h
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#ifndef CSHAPE_H_
#define CSHAPE_H_


#include<iostream>
#include<SDL2/SDL.h>
#include<CArea.h>

class CShape : public CArea {
private:
	int m_toolType;
protected:
	CShape();
public:
	CShape(SDL_Rect frame, SDL_Color color);
	virtual ~CShape();
	virtual void*WriteInFile(FILE*fd)=0;
	void*IsAt(SDL_Point*pAt);
	virtual void Drag(SDL_Point*pAt);

	virtual int GetType()=0;
	virtual SDL_Rect GetFrame();
	virtual SDL_Color GetColor();

	virtual int GetiVertexes();
	virtual SDL_Point*GetpVertexes();
};

#endif /* CSHAPE_H_ */


