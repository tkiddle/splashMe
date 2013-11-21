function colorBoxOpen (jQuerySelector, ajaxUrl, modalWidth, overlayOpacity, overlayColour, modalClose, continueLinkClose) {

	jQuery.ajax({

	    url : ajaxUrl,
	    success : function (data) {
	   
	        var node = jQuery(data),
	            content = node.find(jQuerySelector);

	        jQuery.colorbox({
	            html: content,
	            width: modalWidth,
	            closeButton : false,
	            scrolling : false,
	            opacity : overlayOpacity,
	            onOpen : function () {
	            	if (!modalClose) {
	            		jQuery('#cboxClose').remove();
	            	} 
	            	jQuery('#cboxOverlay').css({
	            		background : overlayColour
	            	});
	            	
	            },
	            onComplete : function () {

	            	jQuery.colorbox.resize();

	            	var contCloseButton = jQuery('a#splash-me-close');

	            	if (continueLinkClose == 1) {
		            	contCloseButton.click( function (e) {
							jQuery.colorbox.close();
							e.preventDefault();
						});
	            	}

	            }
	        });

	    } 

	});


}



window.onload = function () {

	var jQuerySelector = Drupal.settings.splashMe.jQuerySelector,
		ajaxUrl = Drupal.settings.splashMe.ajaxUrl,
		modalWidth = Drupal.settings.splashMe.modalWidth,
		overlayOpacity = Drupal.settings.splashMe.overlayOpacity,
		overlayColour = Drupal.settings.splashMe.overlayColour,
		modalClose = Drupal.settings.splashMe.modalClose == 1 ? true :  false;
		delayTime = Drupal.settings.splashMe.delayTime,
		continueLinkClose = Drupal.settings.splashMe.continueLinkClose;

	if (delayTime) {
		setTimeout(function(){colorBoxOpen(jQuerySelector, ajaxUrl, modalWidth, overlayOpacity, overlayColour, modalClose, continueLinkClose)}, delayTime);
	} else {
		colorBoxOpen(jQuerySelector, ajaxUrl, modalWidth, overlayOpacity, overlayColour, modalClose, continueLinkClose);
	}


}





