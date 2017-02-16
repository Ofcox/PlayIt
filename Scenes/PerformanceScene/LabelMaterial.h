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

/**
 * @brief This class creates textures an materials for labels
 */
class LabelMaterial {
public:
    Ogre::MaterialPtr m_material; /**< Ogre pointer of material */
    static int        m_objectCount; /**< Object counter */

    static std::vector<std::string> m_createdLabels; /**< Container for all already created labels */

    /**
     * @brief Creates label
     *
     * @param Text of the label
     */
    LabelMaterial( std::string text );

    /**
     * @brief Creates the texture of label
     *
     * @param Label text
     * @param Image box
     * @param Label font
     * @param Label colour
     * @param Alignment
     * @param Wrapping of text
     */
    void WriteToTexture( const std::string &str, Ogre::Image::Box destRectangle, Ogre::Font* font, const Ogre::ColourValue &color, char justify = 'l',  bool wordwrap = true );

    /**
     * @brief Returns Ogre pointer to label material
     *
     * @return Ogre::MaterialPtr
     */
    Ogre::MaterialPtr getMaterial() { return m_material; }

private:
    Ogre::Font*      m_font; /**< Label font */
    Ogre::TexturePtr m_destTexture; /**< Ogre pointer to texture */
    std::string      m_materialName; /**< Identification name of material */
    std::string      m_textureName; /**< Identification name of texture */

    /**
     * @brief Check if the label is created
     *
     * @param text
     * @return bool
     */
    bool isAlreadyCreated(std::string& text);
};

#endif // LABELMATERIAL_H
