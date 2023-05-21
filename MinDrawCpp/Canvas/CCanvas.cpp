/*
 * CCanvas.cpp
 *
 *  Created on: 7 oct. 2022
 *      Author: Garnier
 */


#include"CCanvas.h"

CCanvas::CCanvas():CArea(){}

CCanvas::~CCanvas(){}

CCanvas::CCanvas(int iLocX,int iLocY,int iWidth, int iHeight, SDL_Color color):
	CArea(iLocX, iLocY, iWidth, iHeight, color)
{}

void CCanvas::Draw(SDL_Renderer*pRenderer) const{
	CArea::Draw(pRenderer);
	m_Shapes.Parse((t_ptfVV)CCanvas::ShapeDrawMethod, pRenderer);
}

CShape*CCanvas::AddShape(CShape*pShape){

	return(CShape*)m_Shapes.Pushback(pShape);
}

SDL_Rect CCanvas::GetFrame(){
	return m_rFrame;
}

void CCanvas::Flush(){
	m_Shapes.Flush();
}

void CCanvas::Serialize(){
	FILE*fd = fopen("Shape.save", "wb");
	if(fd == NULL){
		SDL_Log ("Failed to open file");
	}
	else{
		size_t nCard = m_Shapes.Card();
		fwrite(&nCard, sizeof nCard, 1,fd);
		m_Shapes.Parse((t_ptfVV)SerializeMethod, (void*)fd);
		fclose(fd);
	}
}

void CCanvas::Unserialize(){
	FILE*fd = fopen("Shape.save", "rb");
	if(fd == NULL){
		SDL_Log ("Failed to open file");
	}
	else{
		m_Shapes.Flush();
		size_t nCard;
		fread(&nCard, sizeof nCard,1,fd);

		SDL_Rect	frame;
		SDL_Color	color;
		int 		typeOfTool;
		int			iVertexes;
		SDL_Point*  pVextexes;

		while(nCard){
			fread(&frame, sizeof(SDL_Rect),1,fd);
			fread(&color, sizeof(SDL_Color),1,fd);
			fread(&typeOfTool, sizeof(int),1,fd);

			switch(typeOfTool){
			case TOOL_RECTANGLE:
				AddShape(new CSrectangle(frame,color));
				break;
			case TOOL_TRIANGLE:
				AddShape(new CStriangle(frame,color));
				break;
			case TOOL_CIRCLE:
				AddShape(new CScircle(frame,color));
				break;
			case TOOL_POLYGON:
				fread(&iVertexes, sizeof(int),1,fd);
				pVextexes = (SDL_Point*)malloc(sizeof(SDL_Point)*iVertexes);
				int k;

				for(k = 0; k <iVertexes;k++){
					fread(&pVextexes[k], sizeof (SDL_Point),1,fd);
				}
				AddShape(new CSpolygon(frame,color,iVertexes,pVextexes));
				break;
			default:
				break;
			}
			nCard--;
		}
		fclose(fd);
	}
}

CShape*CCanvas::ShapeIsAt(SDL_Point pAt){

	return (CShape*)m_Shapes.Parse((t_ptfVV)ShapeIsAtMethod, &pAt);
}

void CCanvas::DeleteShape(SDL_Point pAt){
	m_Shapes.ParseDelif((t_ptfVV)ShapeIsAtMethod, &pAt);
}

CShape*CCanvas::ShapeDeleteMethod(CShape*pShape){
	delete pShape;
	return nullptr;
}

CShape*CCanvas::ShapeDrawMethod(CShape*pShape,SDL_Renderer*pRenderer){
	pShape->Draw(pRenderer);
	return nullptr;
}

CShape*CCanvas::SerializeMethod(CShape*pShape,FILE*fd){
	pShape->WriteInFile(fd);
	return nullptr;
}

CShape*CCanvas::ShapeIsAtMethod(CShape*pShape,SDL_Point*pAt){

	if(pShape->IsAt(pAt)) return pShape;
	return nullptr;
}




CShape*CCanvas::DragMethod(CShape*pShape,SDL_Point pAt){

	pShape->Drag(&pAt);
	return nullptr;
}



