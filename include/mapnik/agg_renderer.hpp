/*****************************************************************************
 * 
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2011 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef MAPNIK_AGG_RENDERER_HPP
#define MAPNIK_AGG_RENDERER_HPP

// mapnik
#include <mapnik/config.hpp>
#include <mapnik/feature_style_processor.hpp>
#include <mapnik/font_engine_freetype.hpp>
#include <mapnik/label_collision_detector.hpp>
#include <mapnik/feature.hpp>


// boost
#include <boost/utility.hpp>
#include <boost/scoped_ptr.hpp>

// FIXME
// forward declare so that
// apps using mapnik do not
// need agg headers
namespace agg {
  struct trans_affine;
}

namespace mapnik {

class Map;
class marker;
struct rasterizer;
struct point_symbolizer;
struct line_symbolizer;
struct line_pattern_symbolizer;
struct polygon_symbolizer;
struct polygon_pattern_symbolizer;
struct raster_symbolizer;
struct shield_symbolizer;
struct text_symbolizer;
struct building_symbolizer;
struct markers_symbolizer;
   
template <typename T>
class MAPNIK_DECL agg_renderer : public feature_style_processor<agg_renderer<T> >,
                                 private boost::noncopyable
{
     
public:
    // create with default, empty placement detector
    agg_renderer(Map const& m, T & pixmap, double scale_factor=1.0, unsigned offset_x=0, unsigned offset_y=0);
    // create with external placement detector, possibly non-empty
    agg_renderer(Map const &m, T & pixmap, boost::shared_ptr<label_collision_detector4> detector,
                 double scale_factor=1.0, unsigned offset_x=0, unsigned offset_y=0);
    ~agg_renderer();
    void start_map_processing(Map const& map);
    void end_map_processing(Map const& map);
    void start_layer_processing(layer const& lay);
    void end_layer_processing(layer const& lay);
    void render_marker(const int x, const int y, marker &marker, const agg::trans_affine & tr, double opacity);

    void process(point_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(line_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(line_pattern_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(polygon_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(polygon_pattern_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(raster_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(shield_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(text_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(building_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void process(markers_symbolizer const& sym,
                 Feature const& feature,
                 proj_transform const& prj_trans);
    void painted(bool painted)
    {
        pixmap_.painted(painted);
    }

private:
    T & pixmap_;
    unsigned width_;
    unsigned height_;
    double scale_factor_;
    CoordTransform t_;
    freetype_engine font_engine_;
    face_manager<freetype_engine> font_manager_;
    boost::shared_ptr<label_collision_detector4> detector_;
    boost::scoped_ptr<rasterizer> ras_ptr;

    void setup(Map const &m);
};
}

#endif // MAPNIK_AGG_RENDERER_HPP
