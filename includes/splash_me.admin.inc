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
		//print_r($themNames['splashme']->info['name']);
		//Create new array to hold form elements
		$form = array();

		$form['splash_me_dev_mode'] = array (
			'#type' => 'checkbox',
			'#title' => t('Developer mode'),
			'#description' => t('Clears the session after 10 seconds rather than 24hrs.'),
			'#default_value' => variable_get('splash_me_dev_mode', 0),
			'#required' => FALSE
		);

		//Add an auto-complete field to the array
		$form['splash_me_node_lookup'] = array(

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

		//Choose between a modal window and a page
		$form['splash_me_view_type'] = array(
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

		//Add an auto-complete field to the array
		$form['splash_me_modal_content'] = array(

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
			'#description' => t("jQuery selector of the content to use in the modal window i.e. #content .main"),
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
		$form['splash_me_modal_width'] = array(

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
			'#description' => t('Width of the modal window see: http://www.jacklmoore.com/colorbox'),
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

		$form['splash_me_modal_close'] = array (
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

		//Add an auto-complete field to the array
		$form['splash_me_modal_delay'] = array(

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
			'#description' => t("The delay time in milliseconds before the modal window appears. Leave blank for no delay."),
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



		$form['splash_me_continue_link'] = array (

			'#type' => 'checkbox',
			'#title' => t('Add a continue link'),
			'#description' => t('Adds a Continue Link to the splash page node.'),
			'#default_value' => variable_get('splash_me_continue_link', 0),
			'#required' => FALSE

		);

		//Add an auto-complete field to the array
		$form['splash_me_continue_link_text'] = array(

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

		$form['splash_me_continue_url'] = array (

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
			    )
			)

		);

		$form['splash_me_themes'] = array (

			'#type' => 'select',
			'#options' => $themesArray,
			'#title' => 'Splash page theme',
			'#description' => 'Select a theme to use for the splash page',
			'#default_value' => variable_get('splash_me_themes'),
			'#required' => FALSE

		);

		unset($themesArray);		

		
		//Once the form is built return it passing the $form array
		return system_settings_form($form);
	  
	}


	//Validation for the configuration form
	function splash_me_admin_validate($form, &$form_state) {
	 
		$continueOption = $form_state['values']['splash_me_continue_link'];
		$continueText = $form_state['values']['splash_me_continue_link_text'];
		$continueUrl = $form_state['values']['splash_me_continue_url'];
		
		//If checkbox is checked but  URL empty
		if($continueOption && !$continueUrl) {

			$errMsg = 'URL for the continue link is required';

			form_set_error('emptyContinueUrl', $errMsg);

		}

		//If checkbox is checked but continue text empty
		if($continueOption && !$continueText) {

			$errMsg = 'Text for the continue link is required';

			form_set_error('emptyContinueText', $errMsg);

		}

	}


