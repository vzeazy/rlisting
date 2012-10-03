(function ($) {
  $(document).ready(function() {
    $('.ajaxpager .pager  a').live('click', function() {
      href = $(this).attr('href');
  //    display = href.indexOf('display');
      display = "pager-display";

      if (href.indexOf('?') == -1){
        href += '?';
      };
      href += '&ajax=1';

      $('#' + display).ajaxStart(function(){
          var html = '<div>';
          html += '<img src="' + Drupal.settings.rlisting['loadingimage'] + '" border="0" />';
          html += '</div>';

        $(this).html(html);
      });

      $.ajax({
        type: "post",
        url: href,
        dataType: 'html',
        success: function(result){
          $('#' + display).hide().html(result).fadeIn('slow');
        }
      });

      return false;
    });
  })
(jQuery);
