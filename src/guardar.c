int guardarHash(Hasht *ht,char *dir){
	FILE *fp;
	mxml_node_t *mxl;
	mxml_node_t *info;
	mxml_node_t *node;
	mxml_node_t *value;
	int tam=ht->size;

	xml=mxmlNewXML("1.0");
	info=mxmlNewElement(xml,"info");
	node=mxmlNewElement(info,"node");
	mxmlNewText(node,0,ht->size);
	value=mxmlNewElement(data,"valores");
	for(int i=0;i<tam;i++){
		node =mxmlNewElement(value,"valores");
		mxmlNewText(node,0,ht->arreglo[i]);
	}
	fp=fopen(dir,"w");
	mxmlSaveFile(xml,fp,MXML_NO_CALLBACK);
	if(fp){
		fclose(fp);
	}else{
		printf("Error en el archivo.\n");
	}
	mxmlDelete(mxl);
}
