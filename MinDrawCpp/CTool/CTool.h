/*
 * Ctools.h
 *
 *  Created on: 7 oct. 2022
 *      Author: Garnier
 */

#ifndef CTOOL_H_
#define CTOOL_H_

#include<iostream>
#include<SDL2/SDL.h>
#include<CArea.h>



class CTool : public CArea {
private:
	int m_toolType;
protected:
	CTool();
public:
	virtual ~CTool();
	CTool(SDL_Color color);

public:	/**** STATIC METHOD *****/

	virtual void*Move(SDL_Rect*frame);
	virtual void SetFrame(SDL_Rect frame);

	static CTool*IsAtMethod(CTool*pTool,SDL_Point*Point);
	virtual int GetType()=0;
	virtual SDL_Color GetColor();

	virtual void*IsAt(SDL_Point*Point);

	virtual SDL_Color GetColorChart(SDL_Point Point);

};

#endif /* CTOOL_H_ */
