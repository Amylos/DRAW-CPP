/*
 * CSpolygon.cpp
 *
 *  Created on: 30 oct. 2022
 *      Author: andre
 */

#include <CSpolygon.h>

CSpolygon::CSpolygon(): CShape(),m_toolType(TOOL_UNDEFINED),m_iVertexes(0),m_pVextexes(nullptr) {}

CSpolygon::~CSpolygon(){}

CSpolygon::CSpolygon(SDL_Rect frame,SDL_Color color,...):CShape(frame, color),m_toolType(TOOL_POLYGON){
    va_list optList;
    va_start(optList, color);

    m_iVertexes = va_arg(optList, int);
    assert(m_iVertexes);

    SDL_Point*pVertexes=va_arg(optList, SDL_Point*);

    m_pVextexes = (SDL_Point*)malloc(sizeof(SDL_Point)*(m_iVertexes+1));
    assert(m_pVextexes);

    int k,
		iXmin = m_pVextexes[0].x,
		iXmax = 0,
		iYmin = m_pVextexes[0].y,
		iYmax = 0;

    for(k=0 ; k < m_iVertexes;k++){
    	m_pVextexes[k] = pVertexes[k];
    	if(iXmin > m_pVextexes[k].x)	iXmin = m_pVextexes[k].x;
		if(iXmax < m_pVextexes[k].x)	iXmax = m_pVextexes[k].x;
		if(iYmin > m_pVextexes[k].y)	iYmin = m_pVextexes[k].y;
		if(iYmax < m_pVextexes[k].y)	iYmax = m_pVextexes[k].y;
//		SDL_Log(" %d %d",m_pVextexes[k].x,m_pVextexes[k].y);
    }

    m_pVextexes[k] = pVertexes[0];
    m_rFrame = (SDL_Rect){iXmin,iYmin,iXmax - iXmin,iYmax - iYmin};
//    SDL_Log(" iXmin %d  iXmax  %d  iYmin %d  iYmax %d",iXmin, iXmax,iYmin,iYmax);
//    SDL_Log("%d %d %d %d ", m_rFrame.x, m_rFrame.y, m_rFrame.w, m_rFrame.h);
    va_end(optList);
}

void CSpolygon::Draw(SDL_Renderer*pRenderer)const{
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawLines(pRenderer, m_pVextexes, m_iVertexes+1);

}

void*CSpolygon::WriteInFile(FILE*fd){
	m_rFrame.w = m_rFrame.h;
	fwrite(&m_rFrame,sizeof(SDL_Rect),1,fd);
	fwrite(&m_color,sizeof(SDL_Color),1,fd);
	fwrite(&m_toolType,sizeof(int),1,fd);
	fwrite(&m_iVertexes,sizeof(int),1,fd);
	for(int k = 0; k<m_iVertexes;k++){
		fwrite(&m_pVextexes[k],sizeof(SDL_Point),1,fd);
	}

	return nullptr;
}

void CSpolygon::Drag(SDL_Point*pAt){

	m_rFrame.x += pAt->x;
	m_rFrame.y += pAt->y;
	for(int k =0;k<=m_iVertexes;k++){
		m_pVextexes[k].x +=  pAt->x;
		m_pVextexes[k].y +=  pAt->y;
	}
}

int CSpolygon::GetType(){
	 return m_toolType;
}

int CSpolygon::GetiVertexes(){
	return m_iVertexes;
}

SDL_Point*CSpolygon::GetpVertexes(){
	return m_pVextexes;
}


