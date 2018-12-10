Group::Group()
{
	this->s.clear();
	this->textureName="";
	this->hasTexture=false;
}
Group::Group(string textureName)
{
	this->s.clear();
	this->textureName=textureName;
	this->hasTexture=true;
}
