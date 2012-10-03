(function ($) {
  Drupal.rlisting = {};
  $(document).ready(function() {

    // top form bar filter
    $('#rlisting-map-form').submit(function(){
      //LoadMapSearch();
      var formVal = $(this).serialize();
      var ajaxURL = Drupal.settings.rlisting.ajaxMarker;
          $('#listing-side').ajaxStart(function(){
              $(this).html(Drupal.rlisting.loadingAnimation());
          });
  
      $.ajax({
        type: "post",
        url: ajaxURL,
        data: formVal,
        dataType: "json",
        success: Drupal.rlisting.createNewMarkers
      }); // end ajax

      return false;
    });

  });

  // When user click on the list on the sidebar.
  $('.map-listing-item').live('click',function() {
    var nid = $(this).attr('id');
    var href = $(this).attr('href');
    var count = $(this).attr('count');
    Drupal.rlisting.triggerMaker(count);
    return false;
  });


  /*********************
  * Filter form has been submitted, we now need to process the form and 
  * return the new markers.
  */
  Drupal.rlisting.createNewMarkers = function(data,textStatus){
    var map = Drupal.gmap.getMap('maplisting');
    map.map.clearOverlays();
    var newMarkers = data['markers'];
    // replace side bar
    //$('#listing-side').html(data['sidebar']);
    $('#listing-side').hide().html(data['sidebar']).fadeIn();
    $('#pager').pager('div.pager');

    var bounds = new GLatLngBounds();

    var tmpMarkers = new Array();
    for(var i=0; i < newMarkers.length; i++){
      var point = new GLatLng(newMarkers[i]['lat'],newMarkers[i]['lon']);
      var html = newMarkers[i]['text'];
      var marker = Drupal.rlisting.createMarker(point, html);
      // we need to reset the marker array so that the click counter
      // corresponds to the markers array.
      //map.vars.markers[i].marker = marker;
      tmpMarkers[i] = new Array();
      tmpMarkers[i]['marker'] = marker;
 
      // add new maker to map.
      map.map.addOverlay(marker);
      bounds.extend(point);
    };
    map.vars.markers = tmpMarkers;

    map.map.setZoom(map.map.getBoundsZoomLevel(bounds) - 1);
    map.map.setCenter(bounds.getCenter());

  }
  Drupal.rlisting.createMarker = function(point,html){
    //var Icon = Drupal.gmap.getIcon(Drupal.settings.gmap['maplisting'].gmap_dynamic_hover_marker,0);
    var marker = new GMarker(point, 'drupal');
    GEvent.addListener(marker, "click", function() {
      marker.openInfoWindowHtml(html);
    });
    return marker;
  }

  /**
  * trigger a click on the markers
  */
  Drupal.rlisting.triggerMaker = function(markerNum) {
    var map = Drupal.gmap.getMap('maplisting');
    //print_r(map.vars.markers);
    GEvent.trigger(map.vars.markers[markerNum].marker, "click");
    //alert(map.vars.latitude);
  }

  /**
   * Load the loading image.
   */
  Drupal.rlisting.loadingAnimation = function() {
  var html = '<div>';

  html += '<img src="' + Drupal.settings.rlisting['loadingimage'] + '" border="0" />';
  html += '</div>';


  return html;
  }

})(jQuery);
