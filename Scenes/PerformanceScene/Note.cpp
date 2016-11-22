#include "Note.h"

ocx::Note::Note( int string, int fret, float timePosition ) {
    m_type		   = NOTE;
    m_isNullFret   = false;
    m_name		   = "";
    m_string	   = string;
    m_strings[0]   = string;
    m_fret		   = fret;
    m_strings[1]   = fret;
    m_timePosition = timePosition;
}

ocx::Note::Note( int string, int fret, float timePosition, bool isNullFret ) {
    m_type		   = NOTE;
    m_isNullFret   = isNullFret;
    m_name		   = "";
    m_string	   = string;
    m_strings[0]   = string;
    m_fret		   = fret;
    m_strings[1]   = fret;
    m_timePosition = timePosition;
}
