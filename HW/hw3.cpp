//
//Author: Brian Lundell
//HW 3
//


list::node *list::findenode(int index) {

	node *p;

	int half = N/2;
	if(index<half) {
		p = head->next;
		for(int i=0; i<=index;i++) {
			p = p->next;
		}
	}
	else {
		p = head->prev;
		for(int i=N; i>=index; i--) {
			p = p->prev;
		}
	}

	return p;
}
