
in vec2 texCoord;

uniform sampler2D tex;

uniform vec4 flashColor;

void main()
{
	vec4 pixel_color = texture2D(tex, texCoord);
	float percent = flashColor.a;

	vec4 colorDifference = vec4(0,0,0,1);

	colorDifference.r = 1.0 - pixel_color.r;
	colorDifference.g = flashColor.g - pixel_color.g;
	colorDifference.b = flashColor.b - pixel_color.b;
	pixel_color.r = pixel_color.r + colorDifference.r * percent;
	pixel_color.g = pixel_color.g +colorDifference.g * percent;
	pixel_color.b =pixel_color.b + colorDifference.b * percent;

	gl_FragColor = pixel_color;
}