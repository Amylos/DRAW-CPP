/*
 * CUtil.cpp
 *
 *  Created on: 14 oct. 2022
 *      Author: Garnier
 */

#include "CUtil.h"

int CUtil::RenderFillPolygon(SDL_Renderer*pRenderer, const SDL_Point*const pVertexes, int iVertexesCount){

	int topY,				/* to hold the y coordinate of the top vertex */
		topCnt,				/* to hold the index of top vertex */
		leftCnt,			/* to hold the index of the vertex left of the top vertex */
		rightCnt,			/* to hold the index of the vertex right of the top vertex */
		startX,				/* starting point do draw the line */
		endX,				/* ending point to draw the line */
		cntY,				/* y position of the current line */
		leftSlope,			/* slope of the left side */
		rightSlope,			/* slope of the right side */
		cnt,				/* counting variable use in loops */
		numVertsProc = 1;	/* number of vertices that have been processed, initialized to 1 */

	SDL_Point center{0};// = CUtil::GetPolygonCenter(pVertexes, iVertexesCount);

	topY = pVertexes[0].y;	/* initialize the top y coordinate to the first point */
	topCnt = 0;				/* set to top point to 0 */

	/* assumes points in counterclockwise order */
	/* find the true top point */
	for(cnt=1; cnt<iVertexesCount; ++cnt){
		if(pVertexes[cnt].y<topY){
			topY = pVertexes[cnt].y;
			topCnt = cnt;
		}
	}

	/* find point to left */
	leftCnt = topCnt - 1;		/* set the left point to one less than the top point */
	if(leftCnt < 0) leftCnt = iVertexesCount - 1;

	/* find point to right */
	rightCnt = topCnt + 1;		/* set the vertex to one more than the top vertex  */
	if(rightCnt >= iVertexesCount) rightCnt = 0;

	startX = endX = (pVertexes[topCnt].x + center.x) << 16;	/* set the starting and ending points of the line */
	cntY = pVertexes[topCnt].y;		/* set the first y value to draw at */

	if(pVertexes[leftCnt].y != pVertexes[topCnt].y) /* if the top and the left do not have the same y value */
		leftSlope = ((pVertexes[leftCnt].x-pVertexes[topCnt].x) << 16)/(pVertexes[leftCnt].y - pVertexes[topCnt].y); /* find the left side slope */

	if(pVertexes[rightCnt].y != pVertexes[topCnt].y) /* if the top and the right do not have the same y value */
		rightSlope = ((pVertexes[rightCnt].x-pVertexes[topCnt].x) << 16)/(pVertexes[rightCnt].y - pVertexes[topCnt].y); /* find the right side slope */

	/* find slopes */
	while(numVertsProc < iVertexesCount){
		/* rasterize to first point */
		while(cntY < pVertexes[leftCnt].y && cntY < pVertexes[rightCnt].y){ /* while one of the two side points has'nt been reached yet */
			SDL_RenderDrawLine(pRenderer, startX >> 16, cntY + center.y, endX >> 16, cntY + center.y);
			cntY++;
			startX += leftSlope;
			endX += rightSlope;
		}
		/* set top point to point met */
		/* set point met to next point */
		/* find new slope */
		if(pVertexes[leftCnt].y <= cntY){ /* if raster line passes the left coordinate */
			topCnt = leftCnt;	/* set the top point to the left side */
			leftCnt--;			/* decrement the left point */
			if(leftCnt < 0){	/* if the left point is less than zero */
				leftCnt = iVertexesCount - 1;	/* wrap around */
			}
			if(pVertexes[leftCnt].y != pVertexes[topCnt].y) /* if the top and left vertex do not have the same y value */
				leftSlope = ((pVertexes[leftCnt].x - pVertexes[topCnt].x) << 16)/(pVertexes[leftCnt].y-pVertexes[topCnt].y); /* find the left side slope */

			startX = (pVertexes[topCnt].x + center.x) << 16;	/* set the starting x position */
			numVertsProc++;		/* increment the number of vertices processed */
		}

		if(pVertexes[rightCnt].y <= cntY){	/* if the raster line passes the right coordinate */
			topCnt = rightCnt;		/* set the top point to the right side */
			rightCnt++;			/* increment the right point */
			if(rightCnt >= iVertexesCount)	/* if the right point is more than the number of vertices */
				rightCnt = 0;	/* et the right point to zero */
			if(pVertexes[rightCnt].y != pVertexes[topCnt].y) /* if the top and new right vertex do not have the same y value */
				rightSlope = ((pVertexes[rightCnt].x - pVertexes[topCnt].x) << 16)/(pVertexes[rightCnt].y - pVertexes[topCnt].y);	/* find the right side slope */

			endX = (pVertexes[topCnt].x + center.x) << 16;	/* set the ending x position */
			numVertsProc++;	/* increment the number of vertices processed */
		}
		SDL_RenderDrawLine(pRenderer, startX >> 16,  cntY + center.y, endX >> 16, cntY + center.y);
	}	/* continue until the number of vertices has touched == number of vertices */

	return 0;
}

SDL_Point CUtil::GetPolygonCenter(const SDL_Point*const pVertexes, int iVertexesCount){

	SDL_Point ptCenter{0};

	for(int k=0;k<iVertexesCount;++k){
		ptCenter.x+=pVertexes[k].x;
		ptCenter.y+=pVertexes[k].y;
	}

	ptCenter.x/=iVertexesCount;
	ptCenter.y/=iVertexesCount;

//	int iXmin = pVertexes[0].x, iXmax = pVertexes[0].x,
//	iYmin = pVertexes[0].y, iYmax = pVertexes[0].y;
//	for(int k=1; k<iVertexesCount; ++k){
//	if(pVertexes[k].x > iXmax) iXmax = pVertexes[k].x;
//	if(pVertexes[k].x < iXmin) iXmin = pVertexes[k].x;
//	if(pVertexes[k].y > iYmax) iYmax = pVertexes[k].y;
//	if(pVertexes[k].y < iYmin) iYmin = pVertexes[k].y;
//	}
//	ptCenter.x = iXmin + (iXmax - iXmin)/2;
//	ptCenter.y = iYmin + (iYmax - iYmin)/2;

	return ptCenter;
}

int CUtil::RenderDrawCircle(SDL_Renderer*pRenderer, SDL_Point ptCenter, int iRadius){
	int iOffsetX = 0,
		iOffsetY = iRadius,
		iD = iRadius - 1,
		iStatus = 0;

	while(iOffsetY >= iOffsetX){
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x + iOffsetX, ptCenter.y + iOffsetY);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x + iOffsetY, ptCenter.y + iOffsetX);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x - iOffsetX, ptCenter.y + iOffsetY);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x - iOffsetY, ptCenter.y + iOffsetX);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x + iOffsetX, ptCenter.y - iOffsetY);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x + iOffsetY, ptCenter.y - iOffsetX);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x - iOffsetX, ptCenter.y - iOffsetY);
		iStatus += SDL_RenderDrawPoint(pRenderer, ptCenter.x - iOffsetY, ptCenter.y - iOffsetX);

		if(iStatus < 0){
			iStatus = -1;
			break;
		}

		if(iD >= 2*iOffsetX){
			iD -= 2*iOffsetX + 1;
			iOffsetX += 1;
		}
		else if(iD < 2*(iRadius - iOffsetY)){
			iD += 2*iOffsetY - 1;
			iOffsetY -= 1;
		}
		else{
			iD += 2*(iOffsetY - iOffsetX -1);
			iOffsetY -= 1;
			iOffsetX += 1;
		}
	}
	return iStatus;

}

int CUtil::RenderFillCircle(SDL_Renderer*pRenderer, SDL_Point ptCenter, int iRadius){

	int iOffsetX = 0,
		iOffsetY = iRadius,
		iD = iRadius - 1,
		iStatus = 0;

	while(iOffsetY >= iOffsetX){
		iStatus += SDL_RenderDrawLine(pRenderer, ptCenter.x - iOffsetY, ptCenter.y + iOffsetX, ptCenter.x + iOffsetY, ptCenter.y + iOffsetX);
		iStatus += SDL_RenderDrawLine(pRenderer, ptCenter.x - iOffsetX, ptCenter.y + iOffsetY, ptCenter.x + iOffsetX, ptCenter.y + iOffsetY);
		iStatus += SDL_RenderDrawLine(pRenderer, ptCenter.x - iOffsetX, ptCenter.y - iOffsetY, ptCenter.x + iOffsetX, ptCenter.y - iOffsetY);
		iStatus += SDL_RenderDrawLine(pRenderer, ptCenter.x - iOffsetY, ptCenter.y - iOffsetX, ptCenter.x + iOffsetY, ptCenter.y - iOffsetX);

		if(iStatus < 0){
			iStatus = -1;
			break;
		}

		if(iD >= 2*iOffsetX){
			iD -= 2*iOffsetX + 1;
			iOffsetX += 1;
		}
		else if(iD < 2*(iRadius - iOffsetY)){
			iD += 2*iOffsetY - 1;
			iOffsetY -= 1;
		}
		else{
			iD += 2*(iOffsetY - iOffsetX -1);
			iOffsetY -= 1;
			iOffsetX += 1;
		}
	}
	return iStatus;
}

int CUtil::RenderDrawTriangle(SDL_Renderer*pRenderer, SDL_Rect frame, int iRadius){

	SDL_RenderDrawLine(pRenderer, frame.x, frame.y + frame.h, frame.x + frame.w, frame.y + frame.h);
	SDL_RenderDrawLine(pRenderer, frame.x, frame.y + frame.h, frame.x + frame.w/2, frame.y);
	SDL_RenderDrawLine(pRenderer, frame.x + frame.w/2, frame.y,frame.x + frame.w, frame.y + frame.h);

	return 1;
}




