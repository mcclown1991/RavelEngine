test_BTAsset = {}

function test_BTAsset.OnStart(me, them)

end

function test_BTAsset.OnDestory(me, them)

end

function test_BTAsset.Update(me, delta)
	DebugLog("BTAsset Update", delta);
end

function test_BTAsset.PrintTask(me, data)
	number = GetValueAsInt(me, "test");
	DebugLog("BTAsset Task print", number);
end

function test_BTAsset.PrintTaskB(me, delta)
	number = GetValueAsBool(me, "test1");
	DebugLog("BTAsset Task print", number);
end

function test_BTAsset.MoveTo(me, delta)
	MoveTo(me, "target", 2);
end