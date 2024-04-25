int variant_validate_is_within_ram(void * address) {
	return ((address != 0) ? 1 : 0);
}

int variant_validate_is_within_flash(void * address) {
	return ((address != 0) ? 1 : 0);
}
