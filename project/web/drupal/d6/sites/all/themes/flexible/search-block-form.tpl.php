<a id="skip_s" />
<input type="text" 
	maxlength="128" 
	name="search_block_form_keys" 
	id="edit-search_block_form_keys"  
	size="25" 
	value="" 
	title="<?php print t('Enter the terms you wish to search for.') ?>" 
	class="form-text" />
<input type="submit" name="op" value="Search"  />
<input type="hidden" name="form_id" id="edit-search-block-form" value="search_block_form" />
<input type="hidden" name="form_token" id="a-unique-id" value="<?php print drupal_get_token('search_block_form'); ?>" />