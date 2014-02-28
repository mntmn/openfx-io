//
//  ofxsCopier.h
//  IO
//
//  Created by Frédéric Devernay on 03/02/2014.
//
//

#ifndef IO_ofxsCopier_h
#define IO_ofxsCopier_h
#include "ofxsPixelProcessor.h"

// Base class for the RGBA and the Alpha processor

// template to do the RGBA processing
template <class PIX, int nComponents>
class PixelCopier : public OFX::PixelProcessorFilterBase {
    public :
    // ctor
    PixelCopier(OFX::ImageEffect &instance)
    : OFX::PixelProcessorFilterBase(instance)
    {}

    // and do some processing
    void multiThreadProcessImages(OfxRectI procWindow)
    {
        for(int y = procWindow.y1; y < procWindow.y2; y++) {
            if(_effect.abort()) break;

            PIX *dstPix = (PIX *) getDstPixelAddress(procWindow.x1, y);

            for(int x = procWindow.x1; x < procWindow.x2; x++) {
                const PIX *srcPix = (const PIX *) getSrcPixelAddress(x, y);
                for(int c = 0; c < nComponents; c++) {
                    dstPix[c] = srcPix[c];
                }
                // increment the dst pixel
                dstPix += nComponents;
            }
        }
    }
};


#endif
