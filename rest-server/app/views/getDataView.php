
{% if totat_use is empty %}
<h1>  nothing to show </h1>

{% else %}
{% for i in totat_use %}
*{{ i.user_uses[:20] }}$
{% endfor %}	
{% endif %}
	

	
