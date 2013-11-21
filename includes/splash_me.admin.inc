<?php 

	/**
	 *@file
	 *splash_me.admin.inc
	 */

	//Create the admin configuration form
	function splash_me_admin() {
	
		$themNames = list_themes($refresh = FALSE);
		$themesArray = array('default' => '--select a theme--');

		
		foreach ($themNames as $item) {

			$key = $item->name;			
			$value = $item->info['name'];
			
			//Is theme enabled?
			if($item->status){
				$themesArray[$key] = $value;
			}

		}
		
		
		//Create new array to hold form elements
		$form = array();

		$form['splash_me'] = array(

			'#type' => 'fieldset',
			'#title' => t('Splash Me Configuration'),
			'#description' => t('Here you can set the options and customise your settings for the Splash Me splash screen module. You can choose between a customasible modal window or full page views.'),
			'#collapsible' => FALSE
		);

		$form['splash_me']['general'] = array(

			'#type' => 'fieldset',
			'#title' => t('General options'),
			'#collapsible' => TRUE,
			'#collapsed' => TRUE,
		);

		//Add an auto-complete field to the array
		$form['splash_me']['general']['splash_me_node_lookup'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Node Title or ID'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_node_lookup'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("Title or ID of the node to be used as splash screen."),
			//Whether the field is required
			'#required' => TRUE,
			//The url to trigger the callback function
			'#autocomplete_path' => 'splash-me-node-results'

		);

		$form['splash_me']['general']['splash_me_themes'] = array (

			'#type' => 'select',
			'#options' => $themesArray,
			'#title' => 'Splash page theme',
			'#description' => 'Select a theme to use for the splash page',
			'#default_value' => variable_get('splash_me_themes'),
			'#required' => FALSE

		);

		unset($themesArray);	

		$form['splash_me']['general']['splash_me_continue_link'] = array (

			'#type' => 'checkbox',
			'#title' => t('Add a continue link'),
			'#description' => t('Adds a Continue Link to the splash page node.'),
			'#default_value' => variable_get('splash_me_continue_link', 0),
			'#required' => FALSE

		);

		$form['splash_me']['general']['splash_me_continue_close_link'] = array (
			'#type' => 'checkbox',
			'#title' => t('Act as a close button'),
			'#description' => t('This link acts as a close button.'),
			'#default_value' => variable_get('splash_me_continue_close_link', 0),
			'#required' => FALSE,
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_continue_link"]' => array('checked' => TRUE),
			    )
			)
		);

		//Add an auto-complete field to the array
		$form['splash_me']['general']['splash_me_continue_link_text'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Continue link text'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_continue_link_text'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("Text to be used in the continue link."),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_continue_link"]' => array('checked' => TRUE),
			    )
			)

		);

		$form['splash_me']['general']['splash_me_continue_url'] = array (

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('URL for the continue link'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_continue_url'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("URL to be used in the continue link i.e. /node/123."),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_continue_link"]' => array('checked' => TRUE),
			      ':input[name="splash_me_continue_close_link"]' => array('checked' => FALSE),
			    )
			)

		);		

		//Choose between a modal window and a page
		$form['splash_me']['general']['splash_me_view_type'] = array(
			//Type of field
			'#type' => 'radios',
			//Label for the field
			'#title' => t('View type'),
			//Options for the radio buttons
			'#options' => array(0 => t('Full page'), 1 => t('Modal window')),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_view_type', 0),
			//Description of the field
			'#description' => t("Choose between a modal window and full page views."),
			//Whether the field is required
			'#required' => TRUE
		);

		$form['splash_me']['colorbox'] = array(

			'#type' => 'fieldset',
			'#title' => t('Modal window Options'),
			//Description of the field
			'#description' => t("Options for you modal window please see http://www.jacklmoore.com/colorbox for color box specific options."),
			//Is the fieldset collapsable
			'#collapsible' => TRUE,
			//fieldset collapsed by default
			'#collapsed' => TRUE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)
		);

		//Add an auto-complete field to the array
		$form['splash_me']['colorbox']['splash_me_modal_content'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('jQuery selector'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_modal_content'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("Selector for the content to use in<br /> the modal window i.e. #content .main"),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)

		);

		//Add an auto-complete field to the array
		$form['splash_me']['colorbox']['splash_me_modal_width'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Modal width'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_modal_width', '50%'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t('Width of the modal window'),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)

		);

		$form['splash_me']['colorbox']['splash_me_modal_opacity'] = array (
			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Overlay opacity'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_modal_opacity', '0.5'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t('Opacity of the modal window overlay. Value between 0 & 1.'),
			//Whether the field is required
			'#required' => TRUE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)
		);

		$form['splash_me']['colorbox']['splash_me_overlay_colour'] = array (
			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Overlay colour'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_overlay_colour', '#000000'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t('Colour of the modal window overlay.'),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)
		);

		//Add an auto-complete field to the array
		$form['splash_me']['colorbox']['splash_me_modal_delay'] = array(

			//Type of field
			'#type' => 'textfield',
			//Label for the field
			'#title' => t('Modal window delay'),
			//Get the value from the DB if it exists
			'#default_value' => variable_get('splash_me_modal_delay'),
			//HTML input width
			'#size' => 40,
			//Max length of chars
			'#maxlength' => 60,
			//Description of the field
			'#description' => t("The delay time in milliseconds before the modal <br />window appears. Leave blank for no delay."),
			//Whether the field is required
			'#required' => FALSE,
			//Visibility state
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)

		);

		$form['splash_me']['colorbox']['splash_me_modal_close'] = array (
			'#type' => 'checkbox',
			'#title' => t('Display a close button'),
			'#description' => t('Displays a close button for the modal window.'),
			'#default_value' => variable_get('splash_me_modal_close', 1),
			'#required' => FALSE,
			'#states' => array(
			    // Only show this field when the 'toggle_me' checkbox is enabled.
			    'visible' => array(
			      ':input[name="splash_me_view_type"]' => array('value' => 1),
			    )
			)
		);

		$form['splash_me']['splash_me_dev_mode'] = array (
			'#field_prefix' => '<br />',
			'#type' => 'checkbox',
			'#title' => t('Developer mode (Clears the session after 10 seconds rather than 24hrs).'),			
			'#default_value' => variable_get('splash_me_dev_mode', 0),
			'#required' => FALSE,
		);	
		
		//Once the form is built return it passing the $form array
		return system_settings_form($form);
	  
	}


	//Validation for the configuration form
	function splash_me_admin_validate($form, &$form_state) {
	 
		$continueOption = $form_state['values']['splash_me_continue_link'];
		$continueCloseOption = $form_state['values']['splash_me_continue_close_link'];
		$continueText = $form_state['values']['splash_me_continue_link_text'];
		$continueUrl = $form_state['values']['splash_me_continue_url'];
		
		//If checkbox is checked but  URL empty
		if($continueOption && !$continueUrl && !$continueCloseOption) {

			$errMsg = 'URL for the continue link is required';

			form_set_error('emptyContinueUrl', $errMsg);

		}

		//If checkbox is checked but continue text empty
		if($continueOption && !$continueText) {

			$errMsg = 'Text for the continue link is required';

			form_set_error('emptyContinueText', $errMsg);

		}

	}


