function colorBoxOpen (jQuerySelector, ajaxUrl, modalWidth, modalClose) {

	jQuery.ajax({

	    url : ajaxUrl,
	    success : function (data) {
	   
	        var node = jQuery(data),
	            content = node.find(jQuerySelector);

	        jQuery.colorbox({
	            html: content,
	            width: modalWidth,
	            closeButton : modalClose,
	            scrolling : false
	        });

	    } 

	});

}

window.onload = function () {

	var jQuerySelector = Drupal.settings.splashMe.jQuerySelector,
		ajaxUrl = Drupal.settings.splashMe.ajaxUrl,
		modalWidth = Drupal.settings.splashMe.modalWidth,
		modalClose = Drupal.settings.splashMe.modalClose == 1 ? true :  false;
		delayTime = Drupal.settings.splashMe.delayTime;

	if (delayTime) {
		setTimeout(function(){colorBoxOpen(jQuerySelector, ajaxUrl, modalWidth, modalClose)}, delayTime);
	} else {
		colorBoxOpen(jQuerySelector, ajaxUrl, modalWidth, modalClose);
	}


}





