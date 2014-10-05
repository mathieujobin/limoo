/*
    Copyright (C) 2014 Sialan Labs
    http://labs.sialan.org

    This project is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This project is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "sialantools.h"

#include <QMetaMethod>
#include <QMetaObject>
#include <QCryptographicHash>
#include <QColor>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <QFileInfo>

QString sialan_tools_numtranslate_0 = "0";
QString sialan_tools_numtranslate_1 = "1";
QString sialan_tools_numtranslate_2 = "2";
QString sialan_tools_numtranslate_3 = "3";
QString sialan_tools_numtranslate_4 = "4";
QString sialan_tools_numtranslate_5 = "5";
QString sialan_tools_numtranslate_6 = "6";
QString sialan_tools_numtranslate_7 = "7";
QString sialan_tools_numtranslate_8 = "8";
QString sialan_tools_numtranslate_9 = "9";


class SialanToolsPrivate
{
public:
};

SialanTools::SialanTools(QObject *parent) :
    QObject(parent)
{
    p = new SialanToolsPrivate;

    sialan_tools_numtranslate_0 = SialanTools::tr("0");
    sialan_tools_numtranslate_1 = SialanTools::tr("1");
    sialan_tools_numtranslate_2 = SialanTools::tr("2");
    sialan_tools_numtranslate_3 = SialanTools::tr("3");
    sialan_tools_numtranslate_4 = SialanTools::tr("4");
    sialan_tools_numtranslate_5 = SialanTools::tr("5");
    sialan_tools_numtranslate_6 = SialanTools::tr("6");
    sialan_tools_numtranslate_7 = SialanTools::tr("7");
    sialan_tools_numtranslate_8 = SialanTools::tr("8");
    sialan_tools_numtranslate_9 = SialanTools::tr("9");
}

void SialanTools::debug(const QVariant &var)
{
    qDebug() << var;
}

QString SialanTools::fileName(const QString &path)
{
    return QFileInfo(path).baseName();
}

QString SialanTools::fileSuffix(const QString &path)
{
    return QFileInfo(path).suffix().toLower();
}

QString SialanTools::readText(const QString &path)
{
    QFile file(path);
    if( !file.open(QFile::ReadOnly) )
        return QString();

    QString res = QString::fromUtf8(file.readAll());
    return res;
}

QString SialanTools::qtVersion()
{
    return qVersion();
}

QString SialanTools::aboutSialan()
{
    return tr("Sialan Labs is a not-for-profit research and software development team launched in February 2014 focusing on development of products, technologies and solutions in order to publish them as open-source projects accessible to all people in the universe. Currently, we are focusing on design and development of software applications and tools which have direct connection with end users.") + "\n\n" +
           tr("By enabling innovative projects and distributing software to millions of users globally, the lab is working to accelerate the growth of high-impact open source software projects and promote an open source culture of accessibility and increased productivity around the world. The lab partners with industry leaders and policy makers to bring open source technologies to new sectors, including education, health and government.");
}

void SialanTools::deleteItemDelay(QObject *o, int ms)
{
    QTimer::singleShot( ms, o, SLOT(deleteLater()) );
}

qreal SialanTools::colorHue(const QColor &clr)
{
    return clr.hue()/255.0;
}

qreal SialanTools::colorLightness(const QColor &clr)
{
    return 2*clr.lightness()/255.0 - 1;
}

qreal SialanTools::colorSaturation(const QColor &clr)
{
    return clr.saturation()/255.0;
}

QString SialanTools::translateNumbers(QString input)
{
    input.replace("0",sialan_tools_numtranslate_0);
    input.replace("1",sialan_tools_numtranslate_1);
    input.replace("2",sialan_tools_numtranslate_2);
    input.replace("3",sialan_tools_numtranslate_3);
    input.replace("4",sialan_tools_numtranslate_4);
    input.replace("5",sialan_tools_numtranslate_5);
    input.replace("6",sialan_tools_numtranslate_6);
    input.replace("7",sialan_tools_numtranslate_7);
    input.replace("8",sialan_tools_numtranslate_8);
    input.replace("9",sialan_tools_numtranslate_9);
    return input;
}

QString SialanTools::passToMd5(const QString &pass)
{
    if( pass.isEmpty() )
        return QString();

    return QCryptographicHash::hash( pass.toUtf8(), QCryptographicHash::Md5 ).toHex();
}

void SialanTools::setProperty(QObject *obj, const QString &property, const QVariant &v)
{
    if( !obj || property.isEmpty() )
        return;

    obj->setProperty( property.toUtf8(), v );
}

QVariant SialanTools::property(QObject *obj, const QString &property)
{
    if( !obj || property.isEmpty() )
        return QVariant();

    return obj->property(property.toUtf8());
}

Qt::LayoutDirection SialanTools::directionOf(const QString &str)
{
    Qt::LayoutDirection res = Qt::LeftToRight;
    if( str.isEmpty() )
        return res;

    int ltr = 0;
    int rtl = 0;

    foreach( const QChar & ch, str )
    {
        QChar::Direction dir = ch.direction();
        switch( static_cast<int>(dir) )
        {
        case QChar::DirL:
        case QChar::DirLRE:
        case QChar::DirLRO:
        case QChar::DirEN:
            ltr++;
            break;

        case QChar::DirR:
        case QChar::DirRLE:
        case QChar::DirRLO:
        case QChar::DirAL:
            rtl++;
            break;
        }
    }

    if( ltr >= rtl )
        res = Qt::LeftToRight;
    else
        res = Qt::RightToLeft;

    return res;
}

QVariant SialanTools::call(QObject *obj, const QString &member, Qt::ConnectionType ctype, const QVariant &v0, const QVariant &v1, const QVariant &v2, const QVariant &v3, const QVariant &v4, const QVariant &v5, const QVariant &v6, const QVariant &v7, const QVariant &v8, const QVariant &v9)
{
    const QMetaObject *meta_obj = obj->metaObject();
    QMetaMethod meta_method;
    for( int i=0; i<meta_obj->methodCount(); i++ )
    {
        QMetaMethod mtd = meta_obj->method(i);
        if( mtd.name() == member )
            meta_method = mtd;
    }
    if( !meta_method.isValid() )
        return QVariant();

    QList<QByteArray> param_types = meta_method.parameterTypes();
    QList<QByteArray> param_names = meta_method.parameterNames();

    QString ret_type = meta_method.typeName();
    QList< QPair<QString,QString> > m_args;
    for( int i=0 ; i<param_types.count() ; i++ )
        m_args << QPair<QString,QString>( param_types.at(i) , param_names.at(i) );

    QVariantList vals;
        vals << v0 << v1 << v2 << v3 << v4 << v5 << v6 << v7 << v8 << v9;

    QVariantList tr_vals;

    QList< QPair<QString,const void*> > args;
    for( int i=0 ; i<vals.count() ; i++ )
    {
        if( i<m_args.count() )
        {
            QString type = m_args.at(i).first;

            if( type != vals.at(i).typeName() )
            {
                if( !vals[i].canConvert( QVariant::nameToType(type.toLatin1()) ) )
                    ;
                else
                    vals[i].convert( QVariant::nameToType(type.toLatin1()) );
            }

            args << QPair<QString,const void*>( type.toLatin1() , vals.at(i).data() );
            tr_vals << vals[i];
        }
        else
        {
            args << QPair<QString,const void*>( vals.at(i).typeName() , vals.at(i).data() );
        }
    }

    int type = QMetaType::type(ret_type.toLatin1());
    void *res = QMetaType::create( type );
    bool is_pointer = ret_type.contains('*');

    bool done;
    switch( static_cast<int>(ctype) )
    {
    case Qt::QueuedConnection:
        done = QMetaObject::invokeMethod( obj , member.toLatin1() , Qt::QueuedConnection ,
                                  QGenericArgument( args.at(0).first.toLatin1() , args.at(0).second ) ,
                                  QGenericArgument( args.at(1).first.toLatin1() , args.at(1).second ) ,
                                  QGenericArgument( args.at(2).first.toLatin1() , args.at(2).second ) ,
                                  QGenericArgument( args.at(3).first.toLatin1() , args.at(3).second ) ,
                                  QGenericArgument( args.at(4).first.toLatin1() , args.at(4).second ) ,
                                  QGenericArgument( args.at(5).first.toLatin1() , args.at(5).second ) ,
                                  QGenericArgument( args.at(6).first.toLatin1() , args.at(6).second ) ,
                                  QGenericArgument( args.at(7).first.toLatin1() , args.at(7).second ) ,
                                  QGenericArgument( args.at(8).first.toLatin1() , args.at(8).second ) ,
                                  QGenericArgument( args.at(9).first.toLatin1() , args.at(9).second ) );
        return QVariant();
        break;

    default:
        done = QMetaObject::invokeMethod( obj , member.toLatin1() , ctype, QGenericReturnArgument( ret_type.toLatin1() , (is_pointer)? &res : res ) ,
                                  QGenericArgument( args.at(0).first.toLatin1() , args.at(0).second ) ,
                                  QGenericArgument( args.at(1).first.toLatin1() , args.at(1).second ) ,
                                  QGenericArgument( args.at(2).first.toLatin1() , args.at(2).second ) ,
                                  QGenericArgument( args.at(3).first.toLatin1() , args.at(3).second ) ,
                                  QGenericArgument( args.at(4).first.toLatin1() , args.at(4).second ) ,
                                  QGenericArgument( args.at(5).first.toLatin1() , args.at(5).second ) ,
                                  QGenericArgument( args.at(6).first.toLatin1() , args.at(6).second ) ,
                                  QGenericArgument( args.at(7).first.toLatin1() , args.at(7).second ) ,
                                  QGenericArgument( args.at(8).first.toLatin1() , args.at(8).second ) ,
                                  QGenericArgument( args.at(9).first.toLatin1() , args.at(9).second ) );
        break;
    }

    QVariant result;
    if( !done )
        return result;

    if( type == QMetaType::Void )
        result = QVariant();
    else
    if( is_pointer )
        result = QVariant( type , &res );
    else
        result = QVariant( type , res );

    if( type == QMetaType::type("QVariant") )
        return result.value<QVariant>();
    else
        return result;
}

SialanTools::~SialanTools()
{
    delete p;
}