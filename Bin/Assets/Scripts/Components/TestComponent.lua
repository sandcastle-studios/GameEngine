print ("Test Component Executed")

function self:Update (aDeltaTime)
	local x, y, z = GetPosition (self.id)
	x = x + speed * aDeltaTime
	z = z - speed * aDeltaTime
	SetPosition(self.id, x, y, z)
end
