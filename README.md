# focus-shapes

A project of ability and focus

# what is this supposed to be

A game in which the objective is to survive wave after wave of generated projectiles, a-la bullet hell. It is still unfinished.

# TODO: 

- Create different projectile types:
	- Actually, not so much projectile types, but "movement engines".
		- Straight.
		- Curved.
		- Around a center.
	- Create a single engine, store a reference.
	- Pass the neccesary data to the engine.
		- This is where shit breaks: we can pass current position but,
		vector might not exist, center might not exist, distance to
		center might not exist....
		- Thus we need additional data... or a single struct will all
		data and get just what we need.
		- So...
		- engine::step(position, delta, additional_data);

- Create emitters.
	- Before that, lay out what you want to achieve, since they must be
	formatted.

- Better ability system (right now it is a prototype).
- Add extend bonus.
- Add combo system.
