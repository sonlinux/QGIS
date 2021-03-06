/***************************************************************************
  qgsdemterraingenerator.h
  --------------------------------------
  Date                 : July 2017
  Copyright            : (C) 2017 by Martin Dobias
  Email                : wonder dot sk at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSDEMTERRAINGENERATOR_H
#define QGSDEMTERRAINGENERATOR_H

#include "qgis_3d.h"

#include "qgsterraingenerator.h"

#include <memory>

class QgsDemHeightMapGenerator;

class QgsRasterLayer;

#include "qgsmaplayerref.h"

/**
 * \ingroup 3d
 * Implementation of terrain generator that uses a raster layer with DEM to build terrain.
 * \since QGIS 3.0
 */
class _3D_EXPORT QgsDemTerrainGenerator : public QgsTerrainGenerator
{
  public:
    QgsDemTerrainGenerator();

    //! Sets raster layer with elevation model to be used for terrain generation
    void setLayer( QgsRasterLayer *layer );
    //! Returns raster layer with elevation model to be used for terrain generation
    QgsRasterLayer *layer() const;

    //! Sets resolution of the generator (how many elevation samples on one side of a terrain tile)
    void setResolution( int resolution ) { mResolution = resolution; updateGenerator(); }
    //! Returns resolution of the generator (how many elevation samples on one side of a terrain tile)
    int resolution() const { return mResolution; }

    //! Returns height map generator object - takes care of extraction of elevations from the layer)
    QgsDemHeightMapGenerator *heightMapGenerator() { return mHeightMapGenerator.get(); }

    virtual QgsTerrainGenerator *clone() const override SIP_FACTORY;
    Type type() const override;
    QgsRectangle extent() const override;
    float heightAt( double x, double y, const Qgs3DMapSettings &map ) const override;
    virtual void writeXml( QDomElement &elem ) const override;
    virtual void readXml( const QDomElement &elem ) override;
    virtual void resolveReferences( const QgsProject &project ) override;

    virtual QgsChunkLoader *createChunkLoader( QgsChunkNode *node ) const override SIP_FACTORY;

  private:
    void updateGenerator();

    std::unique_ptr<QgsDemHeightMapGenerator> mHeightMapGenerator;

    //! source layer for heights
    QgsMapLayerRef mLayer;
    //! how many vertices to place on one side of the tile
    int mResolution;
};


#endif // QGSDEMTERRAINGENERATOR_H
