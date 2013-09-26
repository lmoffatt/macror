#ifndef PLOTTER_H
#define PLOTTER_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include <mgl/mgl.h>
#include <mgl/mgl_zb.h>
#include <mgl/mgl_qt.h>
#include <mgl/mgl_eps.h>
#include <mgl/mgl_data.h>

#include <string>
#include <vector>

namespace Markov_Plot
{

#define LINE_SOLID  "-"
#define LINE_DASHED  "|"
#define LINE_DOTTED  ":"
#define LINE_NONE  " "

#define DOT_SQUARE  "#s"
#define DOT_TRIANGLE  "#v"
#define DOT_CIRCLE  "#o"
#define DOT_CROSS  "#x"
#define DOT_NONE "."

#define COLOR_RED "r"
#define COLOR_GREEN "g"
#define COLOR_BLUE "b"
#define COLOR_BLACK "k"
#define COLOR_GREY "h"
#define COLOR_PURPLE "u"
#define COLOR_ORANGE "q"
#define COLOR_PINK "p"

using namespace std;

/*!
*
*  @module Plot
*  @brief Plotting xy graphics
*
*  MathGL and QT libraries are used to generate
*  xt graphics, an interface is defined to be implemented
*  by all Plottable classes.
*
*/

typedef string line_style;
typedef string line_color;
typedef string dot_style;

/*****************************************************************************//**
*  Plotter work as a mask of the MathGL and QT libraries
*  allowing to easy generate xy graphics, show it and save in files.
*******************************************************************************/

class Plotter
{

public:
    /**
      Constructor
      @post initialize Plotter
      */
    Plotter();

    /**
      Add new curve to existant
      @pre x_data_V has same size than other curves
      @pre width > 0
      @pre dot in DOT_xxx
      @pre line_color in COLOR_xxx
      @post curve added
      */
    void addCurve(vector<double>  x_data_V,
                  string name,
                  line_style style,
                  string width,
                  dot_style dot,
                  line_color color);
    /**
      @pre y_data_V has the same size than others
      @post Steps redefined.
      */
    void defineSteps(vector<double> y_data_V);

    /**
      @pre min <= max
      @post limits redefined
      */
    void setXLimits(double min, double max) { _min_y_lim_d=min; _max_y_lim_d=max; }
    /**
      @pre min <= max
      @post limits redefined
      */
    void setYLimits(double min, double max) { _min_x_lim_d=min; _max_x_lim_d=max; }
    /**
      @pre tick >0, sub_ticks >= 0
      @post ticks redefined
      */
    void setXTicks(double tick, double sub_ticks) { _tick_x_d=tick; _sub_ticks_x_d=sub_ticks;}
    /**
      @pre tick >0, sub_ticks >= 0
      @post ticks redefined
      */
    void setYTicks(double tick, double sub_ticks) { _tick_y_d=tick; _sub_ticks_y_d=sub_ticks; }

    /**
      @pre null
      @post show window with data
      */
    void show(int argc, char* argv[]);
    /**
      @pre null
      @post save file with data
      */
    void save(string file);

private:
    vector< vector<double> > _x_data_V;
    vector<double> _y_data_V;

    vector< string > _names_S;
    vector< line_style > _lines_V;
    vector< line_style > _dots_V;
    vector< string > _widths_V;
    vector< line_color > _colors_V;

    double _min_x_lim_d;double _max_x_lim_d;
    double _min_y_lim_d;double _max_y_lim_d;

    double _tick_x_d, _tick_y_d;
    double _sub_ticks_x_d, _sub_ticks_y_d;

    void set_auto_x_limits();
    void set_auto_y_limits();

};

}
#endif // PLOTTER_H
