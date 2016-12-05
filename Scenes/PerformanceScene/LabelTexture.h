#ifndef LABELTEXTURE_H
#define LABELTEXTURE_H
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreFontManager.h>
#include <OgreFont.h>
#include <OgreMaterialManager.h>
#include <OgreMaterial.h>

#include <OgreTechnique.h>
#include <OgreHardwarePixelBuffer.h>
#include <string>

using namespace Ogre;

/*
   ===============================================================================

    This class creates textures an materials for labels

    TODO:   This class produces a lot of unnecessary objects
            Make it create whole labels objects
            WriteToTexture is potentionaly more useful so make it separate

   ===============================================================================
 */

class LabelTexture
{
public:
    Font*        m_font;
    TexturePtr   m_destTexture;
    MaterialPtr  m_material;
    Ogre::String m_materialName;
    Ogre::String m_textureName;
    static int   m_objectCount;

    LabelTexture( String text );
    void WriteToTexture( const String &str, Image::Box destRectangle, Font* m_font, const ColourValue &color, char justify = 'l',  bool wordwrap = true );
    MaterialPtr getMaterial() {
        return m_material;
    }
};

#endif // LABELTEXTURE_H
