// Control inputs
uniform float Angle; // range 2pi / 100000.0 to 1.0 (rounded down), exponential
uniform float AngleMin; // range -3.2 to 3.2
uniform float AngleWidth; // range 0.0 to 6.4
uniform float Radius; // range -10000.0 to 1.0
uniform float RadiusMin; // range 0.0 to 2.0
uniform float RadiusWidth; // range 0.0 to 2.0
uniform vec2 Center; // range: -1.0 to 3.0

// Texture input
uniform sampler2D Texture;

void main()
{
// Normalised texture coords
vec2 texCoord = gl_TexCoord[0].xy;
// Shift origin to texture centre (with offset)
vec2 normCoord;
normCoord.x = 2.0 * texCoord.x + Center.x;
normCoord.y = 2.0 * texCoord.y + Center.y;
// Convert Cartesian to Polar coords
float r = length(normCoord);
float theta = atan(normCoord.y, normCoord.x);

// The actual effect
//r = (r < RadiusMin) ? r : (r > RadiusMin + RadiusWidth) ? r : ceil(r / Radius) * Radius;
//theta = (theta < AngleMin) ? theta : (theta > AngleMin + AngleWidth) ? theta : floor(theta / Angle) * Angle;

// Convert Polar back to Cartesian coords
normCoord.x = r * cos(theta);
normCoord.y = r * sin(theta);
// Shift origin back to bottom-left (taking offset into account)
texCoord.x = normCoord.x / 2.0 + (Center.x / 2.0);
texCoord.y = normCoord.y / 2.0 + (Center.y / 2.0);

// Output
gl_FragColor = texture2D(Texture, texCoord);
}