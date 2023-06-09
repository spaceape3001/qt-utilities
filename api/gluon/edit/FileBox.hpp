////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <gluon/undo/UndoBase.hpp>
#include <QWidget>
#include <optional>

class QToolButton;

namespace yq::gluon {
    class LineEdit;

    class FileBox : public QWidget, public UndoBase {
        Q_OBJECT
    public:
        FileBox(QWidget*parent=nullptr);
        virtual ~FileBox();
        
        void    setFile(const QString&);
        QString file() const;
        
        void                        set(const std::optional<QString>&);
        std::optional<QString>      get() const;
        
        void    setFilter(const QString&);
        void    setTitle(const QString&);
        
        //  eventually, get UNDO working....
    public slots:
        void        clear();
        void        setReadOnly(bool);
        
    signals:
        void        fileChanged(const QString&);    
    private slots:
        void        browse();
    private:
        QString         m_title;
        QString         m_filter;
        LineEdit*       m_edit;
        QToolButton*    m_button;
    };

}
