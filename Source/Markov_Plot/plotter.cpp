#include <iostream>

#include "Markov_Plot/plotter.h"

namespace Markov_Plot
{

Plotter::Plotter()
{
    _min_x_lim_d=0;
    _min_x_lim_d=0;
    _min_y_lim_d=0;
    _max_y_lim_d=0;
    _tick_x_d=0;
    _tick_y_d=0;
}


void Plotter::addCurve(vector<double>  x_data_V,
                       string name,
                       line_style style,
                       string width,
                       dot_style dot,
                       line_color color)
{
    _x_data_V.push_back(x_data_V);
    _names_S.push_back(name);
    _lines_V.push_back(style);
    _widths_V.push_back(width);
    _dots_V.push_back(dot);
    _colors_V.push_back(color);

    set_auto_x_limits();
}

void Plotter::defineSteps(vector<double> y_data_V)
{
    _y_data_V = y_data_V;

    set_auto_y_limits();
}

void Plotter::save(std::string file)
{
    mglGraphZB gr;

    set_auto_x_limits();
    set_auto_y_limits();

    gr.SetRanges(_min_y_lim_d, _max_y_lim_d, _min_x_lim_d, _max_x_lim_d);
    gr.Alpha(true);

    if (_tick_x_d != 0) gr.SetTicks('x',_tick_x_d, _sub_ticks_x_d);
    if (_tick_y_d != 0) gr.SetTicks('y',_tick_y_d, _sub_ticks_y_d);


    std::vector<std::string> colors;
    if (_colors_V.size() == 0)
    {
        colors.push_back(COLOR_BLACK);
        colors.push_back(COLOR_BLUE);
        colors.push_back(COLOR_GREEN);
        colors.push_back(COLOR_GREY);
        colors.push_back(COLOR_ORANGE);
        colors.push_back(COLOR_PINK);
        colors.push_back(COLOR_PURPLE);
        colors.push_back(COLOR_RED);
    }
    else
        colors = vector<line_color>(_colors_V);

    if (_y_data_V.size()==0)
    {
        _y_data_V.clear();
        for (unsigned int i=0; i<_x_data_V[0].size();i++)
            _y_data_V.push_back(i);
    }

    mglData dv;
    mglData dvy;

/*
    // show data to plot
    std::cout << endl << "Size: " << dv.GetNx() << endl;
    for (int i = 0; i<_x_data_V.size();++i)
    {
        std::cout << _x_data_V[0][i] << endl;
        std::cout << _y_data_V[i] << endl;
    }
*/

    for (int i=0; i<_x_data_V[0].size();++i)
    {
        for (int j=0; j<_x_data_V[0].size();++j)
            dv.Fill(mreal(_x_data_V[i][j]),mreal(_y_data_V[j]));

        //dv[i].Set(_x_data_V[i]);
        //dvy[i].Set(_y_data_V);

        // If lines defined then set, else solid lines
        std::string style = "-";
        if (_lines_V.size() != 0)
            style = _lines_V[i];

        // Dots
        std::string dot = "";
        if (_dots_V.size() != 0)
            dot = _dots_V[i];

        // Widths
        std::string width = "";
        if (_widths_V.size() != 0)
            width = _widths_V[i];

        gr.Step(dv, (colors[i]+width+style+dot).c_str() );
//         gr.Step(dvy[i],dv[i], (colors[i]+width+style+dot).c_str() );
        gr.AddLegend(_names_S[i].c_str(), colors[i].c_str());
    }

    // Width of lines
    gr.SetBaseLineWidth(1);
    // Draw Axes
    gr.Axis();
    // Draw Box
    gr.Box();
    // Draw Legends
    gr.Legend();
    // Write file

    gr.WritePNG("temp.png");//Dontforgettosavetheresult!
    gr.WritePNG(file.c_str());//Dontforgettosavetheresult!


}

void Plotter::set_auto_x_limits()
{
    // Look for min and max x
    _min_x_lim_d=_x_data_V[0][0];
    _max_x_lim_d=_x_data_V[0][0];
    for (unsigned int i=0; i<_x_data_V.size();++i)
        for (unsigned int j=0; j<_x_data_V[i].size();++j)
        {
            if (_x_data_V[i][j] < _min_x_lim_d) _min_x_lim_d = _x_data_V[i][j];
            if (_x_data_V[i][j] > _max_x_lim_d) _max_x_lim_d = _x_data_V[i][j];
        }

    // 20%
    //double ten = (_max_x_lim_d - _min_x_lim_d)/5;
    //_min_x_lim_d-=ten;
    //_max_x_lim_d+=ten;

}

void Plotter::set_auto_y_limits()
{
    if (_y_data_V.size()==0)
    {
        // The limits for y here are the size of data
        _min_y_lim_d=0;
        _max_y_lim_d=_x_data_V[0].size();
    }
    else
    {
        _min_y_lim_d=_y_data_V[0];
        _max_y_lim_d=_y_data_V[0];
        for (unsigned int i=0; i<_y_data_V.size();++i)
        {
            if (_y_data_V[i] < _min_y_lim_d)_min_y_lim_d=_y_data_V[i];
            if (_y_data_V[i] > _max_y_lim_d)_max_y_lim_d=_y_data_V[i];
        }
    }
    // 20%
    //double ten = (_max_y_lim_d - _min_y_lim_d)/5;
    //_min_y_lim_d-=ten;
    //_max_y_lim_d+=ten;

}
}
