/*
 * CSpolygon.h
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#ifndef CSPOLYGON_H_
#define CSPOLYGON_H_

#include<iostream>
#include<defines.h>
#include<SDL2/SDL.h>
#include<CShape.h>
#include<CUtil.h>
#include<cassert>

class CSpolygon : public CShape {
private:
	int 			m_toolType;
	int             m_iVertexes;
	SDL_Point*      m_pVextexes;

private:
	CSpolygon();
public:
	CSpolygon(SDL_Rect frame,SDL_Color color,...);
	virtual ~CSpolygon();
	virtual void Draw(SDL_Renderer*pRenderer)const;
	virtual void*WriteInFile(FILE*fd);
	virtual void Drag(SDL_Point*pAt);
	int GetType();

	virtual int GetiVertexes();
	virtual SDL_Point*GetpVertexes();
};

#endif /* CSPOLYGON_H_ */
