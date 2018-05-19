#ifndef WEBDATAMODEL_H
#define WEBDATAMODEL_H

#include "qgsdatasourceuri.h"
#include <QStandardItemModel>

class QgisInterface;
class QgsMapLayer;
class QNetworkReply;


/**A model for storing services (WFS/WMS/WCS in future) and their layers*/
class WebDataModel: public QStandardItemModel
{
    Q_OBJECT
  public:
    WebDataModel( QgisInterface* iface );
    ~WebDataModel();

    /**Adds service directory and items for service layers to the model
    @param title service title (usually the service name from the combo box)
    @param url service url
    @param serviceName WMS/WFS/WCS*/
    void addService( const QString& title, const QString& url, const QString& service );

    void addEntryToMap( const QModelIndex& index );
    void removeEntryFromMap( const QModelIndex& index );
    void changeEntryToOffline( const QModelIndex& index );
    void changeEntryToOnline( const QModelIndex& index );
    void reload( const QModelIndex& index );

    QString layerStatus( const QModelIndex& index ) const ;
    bool layerInMap( const QModelIndex& index ) const;

  private slots:
    void wmsCapabilitiesRequestFinished();
    void wfsCapabilitiesRequestFinished();
    void handleItemChange( QStandardItem* item );
    void syncLayerRemove( QStringList theLayerIds );

  signals:
    void serviceAdded();

  private:
    QNetworkReply *mCapabilitiesReply;
    QgisInterface* mIface;

    QString wfsUrlFromLayerIndex( const QModelIndex& index ) const;
    QgsDataSourceUri wmsUriFromIndex( const QModelIndex& index ) const;
    QString layerName( const QModelIndex& index ) const;
    QString serviceType( const QModelIndex& index ) const;


    /**Exchanges a layer in the map canvas (and copies the style of the new layer to the old one)*/
    bool exchangeLayer( const QString& layerId, QgsMapLayer* newLayer );
    void deleteOfflineDatasource( const QString& serviceType, const QString& offlinePath );

    /**Returns id of layer in current map with given url (or empty string if no such layer)*/
    static QString layerIdFromUrl( const QString& url, const QString& serviceType, bool online,
                                   const QString& layerName );

    void loadFromXML();
    void saveToXML() const;

    /**Returns path to web.xml. Creates the file if not there*/
    QString xmlFilePath() const;

    /**Modes a layer after ml in the legend tree*/
    void legendMoveLayer( const QgsMapLayer* ml, const QgsMapLayer* after );
};

#endif //WEBDATAMODEL_H
