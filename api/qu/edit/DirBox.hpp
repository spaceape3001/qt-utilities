////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QWidget>
#include <optional>
#include <qu/undo/UndoBase.hpp>

class QToolButton;

namespace qu {

    class LineEdit;
    class DirBox : public QWidget, public UndoBase {
        Q_OBJECT
    public:
        DirBox(QWidget*parent=nullptr);
        virtual ~DirBox();
        
        void                        set(const std::optional<QString>&);
        std::optional<QString>      get() const;

        void    setDirPath(const QString&);
        QString dirPath() const;
        void    setTitle(const QString&);
        
        //  eventually, get UNDO working....
    public slots:
        void        clear();
        void        setReadOnly(bool);
    signals:
        void        dirPathChanged(const QString&);    
    private slots:
        void        browse();
    private:
        QString         m_title;
        LineEdit*       m_edit;
        QToolButton*    m_button;
    };

}
