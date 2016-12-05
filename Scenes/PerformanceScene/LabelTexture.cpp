#include "LabelTexture.h"

int LabelTexture::m_objectCount = 0;

LabelTexture::LabelTexture( String text ) {

    m_materialName = "mat_";
    m_textureName  = "tex_";
    m_objectCount++;

    m_materialName.append(Ogre::StringConverter::toString(m_objectCount) );
    m_textureName.append(Ogre::StringConverter::toString(m_objectCount) );
    m_font = FontManager::getSingleton().getByName( "SdkTrays/Caption" ).getPointer();

    // Make sure the texture is not WRITE_ONLY, we need to read the buffer to do the blending with the font (get the alpha for example)
    m_destTexture = TextureManager::getSingleton().createManual( m_textureName.c_str() /*"LabelTexture"*/,"General",TEX_TYPE_2D, 512, 512, MIP_UNLIMITED, PF_X8R8G8B8, Ogre::TU_STATIC | Ogre::TU_AUTOMIPMAP ) /*.getPointer()*/;

    WriteToTexture( text.c_str(), Image::Box( 50,50,150,150 ),m_font,ColourValue( 1.0,1.0,1.0,1.0 ),'c' );

    m_material = MaterialManager::getSingleton().create(m_materialName.c_str() /*"LabelMaterial"*/, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    m_material->getTechnique(0)->getPass(0)->setSceneBlending(SBT_ADD);
    m_material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
    m_material->getTechnique(0)->getPass(0)->createTextureUnitState(m_textureName.c_str() /*"LabelTexture"*/);
}

void LabelTexture::WriteToTexture( const String &str, Image::Box destRectangle, Font *font, const ColourValue &color, char justify, bool wordwrap ) {
    if ( m_destTexture->getHeight() < destRectangle.bottom ) {
        destRectangle.bottom = m_destTexture->getHeight();
    }
    if ( m_destTexture->getWidth() < destRectangle.right ) {
        destRectangle.right = m_destTexture->getWidth();
    }

    if ( !font->isLoaded() ) {
        font->load();
    }

    TexturePtr fontTexture = (TexturePtr) TextureManager::getSingleton().getByName( font->getMaterial()->getTechnique( 0 )->getPass( 0 )->getTextureUnitState( 0 )->getTextureName() );

    HardwarePixelBufferSharedPtr fontBuffer = fontTexture->getBuffer();
    HardwarePixelBufferSharedPtr destBuffer = m_destTexture->getBuffer();

    PixelBox destPb = destBuffer->lock( destRectangle,HardwareBuffer::HBL_NORMAL );

    // The font texture buffer was created write only...so we cannot read it back :o). One solution is to copy the buffer  instead of locking it. (Maybe there is a way to create a font texture which is not write_only ?)

    // create a buffer
    size_t nBuffSize = fontBuffer->getSizeInBytes();
    uint8* buffer    = (uint8*)calloc( nBuffSize, sizeof( uint8 ) );

    // create pixel box using the copy of the buffer
    PixelBox fontPb( fontBuffer->getWidth(), fontBuffer->getHeight(),fontBuffer->getDepth(), fontBuffer->getFormat(), buffer );
    fontBuffer->blitToMemory( fontPb );

    uint8* fontData = static_cast<uint8*>( fontPb.data );
    uint8* destData = static_cast<uint8*>( destPb.data );

    const size_t fontPixelSize = PixelUtil::getNumElemBytes( fontPb.format );
    const size_t destPixelSize = PixelUtil::getNumElemBytes( destPb.format );

    const size_t fontRowPitchBytes = fontPb.rowPitch * fontPixelSize;
    const size_t destRowPitchBytes = destPb.rowPitch * destPixelSize;

    Box *GlyphTexCoords;
    GlyphTexCoords = new Box[str.size()];

    Font::UVRect glypheTexRect;
    size_t       charheight = 0;
    size_t       charwidth  = 0;

    for ( unsigned int i = 0; i < str.size(); i++ )
    {
        if ( ( str[i] != '\t' ) && ( str[i] != '\n' ) && ( str[i] != ' ' ) ) {
            glypheTexRect            = font->getGlyphTexCoords( str[i] );
            GlyphTexCoords[i].left   = glypheTexRect.left * fontTexture->getSrcWidth();
            GlyphTexCoords[i].top    = glypheTexRect.top * fontTexture->getSrcHeight();
            GlyphTexCoords[i].right  = glypheTexRect.right * fontTexture->getSrcWidth();
            GlyphTexCoords[i].bottom = glypheTexRect.bottom * fontTexture->getSrcHeight();

            if ( GlyphTexCoords[i].getHeight() > charheight ) {
                charheight = GlyphTexCoords[i].getHeight();
            }
            if ( GlyphTexCoords[i].getWidth() > charwidth ) {
                charwidth = GlyphTexCoords[i].getWidth();
            }
        }

    }

    size_t cursorX = 0;
    size_t cursorY = 0;
    size_t lineend = destRectangle.getWidth();

    bool carriagreturn = true;
    for ( unsigned int strindex = 0; strindex < str.size(); strindex++ )
    {
        switch ( str[strindex] )
        {
        case ' ': cursorX  += charwidth;  break;
        case '\t': cursorX += charwidth * 3; break;
        case '\n': cursorY += charheight; carriagreturn = true; break;
        default:
        {
            //wrapping
            if ( ( cursorX + GlyphTexCoords[strindex].getWidth() > lineend ) && !carriagreturn ) {
                cursorY      += charheight;
                carriagreturn = true;
            }

            //justify
            if ( carriagreturn ) {
                size_t l         = strindex;
                size_t textwidth = 0;
                size_t wordwidth = 0;

                while ( ( l < str.size() ) && ( str[l] != '\n)' ) )
                {
                    wordwidth = 0;

                    switch ( str[l] )
                    {
                    case ' ': wordwidth  = charwidth; ++l; break;
                    case '\t': wordwidth = charwidth * 3; ++l; break;
                    case '\n': l         = str.size();
                    }

                    if ( wordwrap ) {
                        while ( ( l < str.size() ) && ( str[l] != ' ' ) && ( str[l] != '\t' ) && ( str[l] != '\n' ) )
                        {
                            wordwidth += GlyphTexCoords[l].getWidth();
                            ++l;
                        }
                    } else
                    {
                        wordwidth += GlyphTexCoords[l].getWidth();
                        l++;
                    }

                    if ( ( textwidth + wordwidth ) <= destRectangle.getWidth() ) {
                        textwidth += ( wordwidth );
                    } else {
                        break;
                    }
                }

                if ( ( textwidth == 0 ) && ( wordwidth > destRectangle.getWidth() ) ) {
                    textwidth = destRectangle.getWidth();
                }

                switch ( justify )
                {
                case 'c': cursorX = ( destRectangle.getWidth() - textwidth ) / 2;
                    lineend       = destRectangle.getWidth() - cursorX;
                    break;

                case 'r': cursorX = ( destRectangle.getWidth() - textwidth );
                    lineend       = destRectangle.getWidth();
                    break;

                default: cursorX = 0;
                    lineend      = textwidth;
                    break;
                }

                carriagreturn = false;
            }

            //abort - net enough space to draw
            if ( ( cursorY + charheight ) > destRectangle.getHeight() ) {
                goto stop;
            }

            //draw pixel by pixel
            for ( size_t i = 0; i < GlyphTexCoords[strindex].getHeight(); i++ )
                for ( size_t j = 0; j < GlyphTexCoords[strindex].getWidth(); j++ )
                {
                    float  alpha    =  color.a * ( fontData[( i + GlyphTexCoords[strindex].top ) * fontRowPitchBytes + ( j + GlyphTexCoords[strindex].left ) * fontPixelSize + 1 ] / 255.0 );
                    float  invalpha = 1.0 - alpha;
                    size_t offset   = ( i + cursorY ) * destRowPitchBytes + ( j + cursorX ) * destPixelSize;

                    ColourValue pix;
                    PixelUtil::unpackColour( &pix,destPb.format,&destData[offset] );
                    pix = ( pix * invalpha ) + ( color * alpha );
                    PixelUtil::packColour( pix,destPb.format,&destData[offset] );
                }

            cursorX += GlyphTexCoords[strindex].getWidth();
        }    //default
        }//switch
    }//for

stop:
    delete[] GlyphTexCoords;

    destBuffer->unlock();

    // Free the memory allocated for the buffer
    free( buffer ); buffer = 0;
}
