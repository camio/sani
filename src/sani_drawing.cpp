#include <sani/drawing.hpp>

#include <boost/bind.hpp>
#include <QPainter>

namespace sani {

    // Return the specified 'degreesValue', which is in degrees units, in 16ths of a degree units. Note that 16ths of a degree is the standard angle unit in the Qt library.
    static int degToDeg16( const qreal & r )
    {
        return r * 16;
    }

    Drawing drawLine( const QPen & pen, const QPointF & p1, const QPointF & p2 )
    {
        return DrawLine( pen, p1, p2 );
    }
    Drawing drawPoint( const QPen & pen, const QPointF & p )
    {
        return DrawPoint( pen, p );
    }
    Drawing drawRect( const QPen & pen, const QBrush & brush, const QRectF & rect )
    {
        return DrawRect( pen, brush, rect );
    }
    Drawing drawEllipse( const QPen & pen, const QBrush & brush, const QRectF & rect )
    {
        return DrawEllipse( pen, brush, rect );
    }
    Drawing drawRoundedRect
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & xRadius
        , const double & yRadius
        , const bool absolute
        )
    {
        return DrawRoundedRect( pen, brush, rect, xRadius, yRadius, absolute );
    }
    Drawing drawText
        ( const QPen & pen
        , const QBrush & brush
        , const QFont & font
        , const QPointF & position
        , const std::string & text
        )
    {
        return DrawText( pen, brush, font, position, text );
    }
    Drawing drawArc
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & startAngle
        , const double & spanAngle
        )
    {
        return DrawArc( pen, brush, rect, startAngle, spanAngle );
    }
    Drawing drawPie
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & startAngle
        , const double & spanAngle
        )
    {
        return DrawPie( pen, brush, rect, startAngle, spanAngle );
    }
    Drawing drawChord
        ( const QPen & pen
        , const QBrush & brush
        , const QRectF & rect
        , const double & startAngle
        , const double & spanAngle
        )
    {
        return DrawChord( pen, brush, rect, startAngle, spanAngle );
    }
    Drawing drawOver( const Drawing & a, const Drawing & b )
    {
        return DrawOver( a, b );
    }
    Drawing transformDrawing( const QTransform & t, const Drawing & d )
    {
        return DrawTransform( t, d );
    }
    struct Draw
    {
        typedef void result_type;
        void operator()
            ( QPainter & painter
            , const DrawPoint & d
            ) const
        {
            painter.setPen( d.pen );
            painter.drawPoint( d.p );
        }
        void operator()
            ( QPainter & painter
            , const DrawLine & d
            ) const
        {
            painter.setPen( d.pen );
            painter.drawLine( d.p1, d.p2 );
        }
        void operator()
            ( QPainter & painter
            , const DrawRect & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.drawRect( d.rect );
        }
        void operator()
            ( QPainter & painter
            , const DrawRoundedRect & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.drawRoundedRect
                ( d.rect
                , d.xRadius
                , d.yRadius
                , d.absolute
                    ? Qt::AbsoluteSize
                    : Qt::RelativeSize
                );
        }
        void operator()
            ( QPainter & painter
            , const DrawText & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.setFont( d.font );
            painter.drawText
                ( d.position
                , QString::fromUtf8( d.text.data(), int( d.text.size() ) )
                );
        }
        void operator()
            ( QPainter & painter
            , const DrawEllipse & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.drawEllipse( d.rect );
        }
        void operator()
            ( QPainter & painter
            , const DrawArc & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.drawArc
                ( d.rect
                , degToDeg16( d.startAngle )
                , degToDeg16( d.spanAngle )
                );
        }
        void operator()
            ( QPainter & painter
            , const DrawPie & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.drawPie
                ( d.rect
                , degToDeg16( d.startAngle )
                , degToDeg16( d.spanAngle )
                );
        }
        void operator()
            ( QPainter & painter
            , const DrawChord & d
            ) const
        {
            painter.setPen( d.pen );
            painter.setBrush( d.brush );
            painter.drawChord
                ( d.rect
                , degToDeg16( d.startAngle )
                , degToDeg16( d.spanAngle )
                );
        }
        void operator()
            ( QPainter & painter
            , const DrawNothing &
            ) const
        {
        }
        void operator()
            ( QPainter & painter
            , const DrawOver & d
            ) const
        {
            draw( d.d2, painter );
            draw( d.d1, painter );
        }
        void operator()
            ( QPainter & painter
            , const DrawTransform & t
            ) const
        {
            painter.save();
            painter.setTransform( t.t, true );
            draw( t.d, painter );
            painter.restore();
        }
    };

    void draw( const Drawing & d, QPainter & painter )
    {
        return boost::apply_visitor
            ( boost::bind
             ( Draw()
             , boost::ref( painter )
             , _1
             )
            , d
            );
    }
}
