#ifndef SANI_DRAWING_HPP_
#define SANI_DRAWING_HPP_

#include <QPen>
#include <QBrush>
#include <QPointF>
#include <QRectF>
#include <QFont>
#include <QTransform>

#include <boost/variant.hpp>

namespace sani {
    struct DrawLine
    {
        DrawLine() {};
        DrawLine
            ( const QPen & pen_
            , const QPointF & p1_
            , const QPointF & p2_
            )
            : pen( pen_ )
            , p1( p1_ )
            , p2( p2_ )
        {
        }
        QPen pen;
        QPointF p1;
        QPointF p2;
    };
    struct DrawRect
    {
        DrawRect() {};
        DrawRect
            ( const QPen & pen_
            , const QBrush & brush_
            , const QRectF & rect_
            )
            : pen( pen_ )
            , brush( brush_ )
            , rect( rect_ )
        {
        }
        QPen pen;
        QBrush brush;
        QRectF rect;
    };
    struct DrawText
    {
        DrawText() {};
        DrawText
            ( const QPen & pen_
            , const QBrush & brush_
            , const QFont & font_
            , const QPointF & position_
            , const std::string & text_
            )
            : pen( pen_ )
            , brush( brush_ )
            , font( font_ )
            , position( position_ )
            , text( text_ )
        {
        }
        QPen pen;
        QBrush brush;
        QFont font;
        QPointF position;
        std::string text;
    };
    struct DrawEllipse
    {
        DrawEllipse() {};
        DrawEllipse
            ( const QPen & pen_
            , const QBrush & brush_
            , const QRectF & rect_
            )
            : pen( pen_ )
            , brush( brush_ )
            , rect( rect_ )
        {
        }
        QPen pen;
        QBrush brush;
        QRectF rect;
    };
    struct DrawArc
    {
        DrawArc() {};
        DrawArc
            ( const QPen & pen_
            , const QBrush & brush_
            , const QRectF & rect_
            , const double & startAngle_
            , const double & spanAngle_
            )
            : pen( pen_ )
            , brush( brush_ )
            , rect( rect_ )
            , startAngle( startAngle_ )
            , spanAngle( spanAngle_ )
        {
        }
        QPen pen;
        QBrush brush;
        QRectF rect;
        double startAngle;
        double spanAngle;
    };
    struct DrawPie
    {
        DrawPie() {};
        DrawPie
            ( const QPen & pen_
            , const QBrush & brush_
            , const QRectF & rect_
            , const double & startAngle_
            , const double & spanAngle_
            )
            : pen( pen_ )
            , brush( brush_ )
            , rect( rect_ )
            , startAngle( startAngle_ )
            , spanAngle( spanAngle_ )
        {
        }
        QPen pen;
        QBrush brush;
        QRectF rect;
        double startAngle;
        double spanAngle;
    };
    struct DrawChord
    {
        DrawChord() {};
        DrawChord
            ( const QPen & pen_
            , const QBrush & brush_
            , const QRectF & rect_
            , const double & startAngle_
            , const double & spanAngle_
            )
            : pen( pen_ )
            , brush( brush_ )
            , rect( rect_ )
            , startAngle( startAngle_ )
            , spanAngle( spanAngle_ )
        {
        }
        QPen pen;
        QBrush brush;
        QRectF rect;
        double startAngle;
        double spanAngle;
    };
    struct DrawRoundedRect
    {
        DrawRoundedRect() {};
        DrawRoundedRect
            ( const QPen & pen_
            , const QBrush & brush_
            , const QRectF & rect_
            , const double & xRadius_
            , const double & yRadius_
            , const bool absolute_
            )
            : pen( pen_ )
            , brush( brush_ )
            , rect( rect_ )
            , xRadius( xRadius_ )
            , yRadius( yRadius_ )
            , absolute( absolute_ )
        {
        }
        QPen pen;
        QBrush brush;
        QRectF rect;
        double xRadius;
        double yRadius;
        bool absolute;
    };
    struct DrawPoint
    {
        DrawPoint() {};
        DrawPoint
            ( const QPen & pen_
            , const QPointF & p_
            )
            : pen( pen_ )
            , p( p_ )
        {
        }
        QPen pen;
        QPointF p;
    };
    template< typename Drawing >
    struct DrawOverG
    {
        DrawOverG(){}
        DrawOverG( const Drawing & d1_, const Drawing & d2_ )
            : d1( d1_ )
            , d2( d2_ )
        {
        }
        Drawing d1;
        Drawing d2;
    };
    template< typename Drawing >
    struct DrawTransformG
    {
        DrawTransformG(){}
        DrawTransformG( const QTransform & t_, const Drawing & d_ )
            : t( t_ )
            , d( d_ )
        {
        }
        QTransform t;
        Drawing d;
    };
    struct DrawNothing
    {
    };

    struct Drawing
        : boost::variant
            < DrawPoint
            , DrawLine
            , DrawRect
            , DrawRoundedRect
            , DrawText
            , DrawEllipse
            , DrawArc
            , DrawPie
            , DrawChord
            , DrawNothing
            , boost::recursive_wrapper< DrawOverG< Drawing > >
            , boost::recursive_wrapper< DrawTransformG< Drawing > >
            >
    {
        typedef boost::variant
            < DrawPoint
            , DrawLine
            , DrawRect
            , DrawRoundedRect
            , DrawText
            , DrawEllipse
            , DrawArc
            , DrawPie
            , DrawChord
            , DrawNothing
            , boost::recursive_wrapper< DrawOverG< Drawing > >
            , boost::recursive_wrapper< DrawTransformG< Drawing > >
            > Base;

        Drawing(){}
        template< typename T >
        Drawing( const T & t )
            : Base( t )
        {
        }
        Drawing& operator=(const Drawing& other)
        {
            *static_cast<Base*>(this) = static_cast<const Base&>(other);
            return(*this);
        }
        //See: https://svn.boost.org/trac/boost/ticket/592
        Drawing(const Drawing& other)
            : Base(static_cast<const Base&>(other))
        {
        }
    };
    typedef DrawOverG<Drawing> DrawOver;
    typedef DrawTransformG<Drawing> DrawTransform;

    Drawing drawLine( const QPen & pen, const QPointF & p1, const QPointF & p2 );
    Drawing drawPoint( const QPen & pen, const QPointF & p );
    Drawing drawRect( const QPen & pen, const QBrush & brush, const QRectF & rect );
    Drawing drawEllipse( const QPen & pen, const QBrush & brush, const QRectF & rect );
    Drawing drawRoundedRect
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & xRadius
        , const double & yRadius
        , const bool absolute
        );
    Drawing drawText
        ( const QPen & pen
        , const QBrush & brush
        , const QFont & font
        , const QPointF & position
        , const std::string & text
        );
    Drawing drawArc
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & startAngle
        , const double & spanAngle
        );
    Drawing drawPie
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & startAngle
        , const double & spanAngle
        );
    Drawing drawChord
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & startAngle
        , const double & spanAngle
        );
    Drawing transformDrawing( const QTransform & t, const Drawing & d );
    Drawing drawOver( const Drawing & a, const Drawing & b );
    const Drawing drawNothing = DrawNothing();

    void draw( const Drawing & d, QPainter & painter );
}

#endif
