local Entity = {}
Entity.__index = Entity

function Entity:add_component(type, args)
  local obj = {}
  obj.index = self.index
  obj.version = self.version
  obj.type = type
  if args == nil then
    obj.args = {}
  else
    obj.args = args
  end
  e_add_component(obj)
end

function Entity:create_entity()
  local e = {}
  setmetatable(e, Entity)
  e.index, e.version = e_create_entity()
  return e
end

return Entity
