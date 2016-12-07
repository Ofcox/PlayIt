#ifndef LABELMATERIAL_H
#define LABELMATERIAL_H
#include <OgreTextureManager.h>
#include <OgreTexture.h>
#include <OgreFontManager.h>
#include <OgreFont.h>
#include <OgreMaterialManager.h>
#include <OgreMaterial.h>

#include <OgreTechnique.h>
#include <OgreHardwarePixelBuffer.h>
#include <string>
#include <vector>

/*
   ===============================================================================

    This class creates textures an materials for labels

   ===============================================================================
*/

class LabelMaterial{
private:
    Ogre::Font*       m_font;
    Ogre::TexturePtr  m_destTexture;
    std::string m_materialName;
    std::string m_textureName;
    bool isAlreadyCreated(std::string& text);
public:

    Ogre::MaterialPtr m_material;
    static int   m_objectCount;

    static std::vector<std::string> m_createdLabels;

    LabelMaterial( std::string text );
    void WriteToTexture( const std::string &str, Ogre::Image::Box destRectangle, Ogre::Font* m_font, const Ogre::ColourValue &color, char justify = 'l',  bool wordwrap = true );
    Ogre::MaterialPtr getMaterial() {
        return m_material;
    }
};

#endif // LABELMATERIAL_H
